#include <iostream>
#include <vector>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include "ws2811.h"

class LED {
public:
    LED(int width = 8, int height = 8, int gpio_pin = 18, int dma = 10, int strip_type = WS2811_STRIP_GBR);
    ~LED();
    void run();
    void stop();
    void clearMatrix();

private:
    int width;
    int height;
    int led_count;
    int gpio_pin;
    int dma;
    int strip_type;
    int clear_on_exit;

    ws2811_t ledstring;
    ws2811_led_t* matrix;
    static bool running;

    void setupHandlers();
    static void ctrlCHandler(int signum);
    void matrixRender();
    void matrixRaise();
    void matrixBottom();

    std::vector<int> dotspos;
    std::vector<ws2811_led_t> dotcolors;
    std::vector<ws2811_led_t> dotcolors_rgbw;
};

bool LED::running = true;

LED::LED(int width, int height, int gpio_pin, int dma, int strip_type)
    : width(width), height(height), gpio_pin(gpio_pin), dma(dma), strip_type(strip_type), clear_on_exit(0) {
    led_count = width * height;
    
    ledstring = {
        .freq = WS2811_TARGET_FREQ,
        .dmanum = dma,
        .channel =
            {
                [0] =
                    {
                        .gpionum = gpio_pin,
                        .invert = 0,
                        .count = led_count,
                        .strip_type = strip_type,
                        .brightness = 255,
                    },
                [1] =
                    {
                        .gpionum = 0,
                        .invert = 0,
                        .count = 0,
                        .brightness = 0,
                    },
            },
    };

    matrix = new ws2811_led_t[led_count];
    dotspos = {0, 1, 2, 3, 4, 5, 6, 7};
    dotcolors = {
        0x00200000, // red
        0x00201000, // orange
        0x00202000, // yellow
        0x00002000, // green
        0x00002020, // lightblue
        0x00000020, // blue
        0x00100010, // purple
        0x00200010, // pink
    };

    dotcolors_rgbw = {
        0x00200000, // red
        0x10200000, // red + W
        0x00002000, // green
        0x10002000, // green + W
        0x00000020, // blue
        0x10000020, // blue + W
        0x00101010, // white
        0x10101010, // white + W
    };

    setupHandlers();
    if (ws2811_init(&ledstring) != WS2811_SUCCESS) {
        std::cerr << "ws2811_init failed." << std::endl;
        throw std::runtime_error("Initialization failed.");
    }
}

LED::~LED() {
    if (clear_on_exit) {
        clearMatrix();
        matrixRender();
        ws2811_render(&ledstring);
    }
    ws2811_fini(&ledstring);
    delete[] matrix;
}

void LED::run() {
    while (running) {
        matrixRaise();
        matrixBottom();
        matrixRender();
        if (ws2811_render(&ledstring) != WS2811_SUCCESS) {
            std::cerr << "ws2811_render failed." << std::endl;
            break;
        }
        usleep(1000000 / 15); // 15 frames / sec
    }
}

void LED::stop() {
    running = false;
}

void LED::clearMatrix() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            matrix[y * width + x] = 0;
        }
    }
}

void LED::matrixRender() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
        }
    }
}

void LED::matrixRaise() {
    for (int y = 0; y < (height - 1); y++) {
        for (int x = 0; x < width; x++) {
            matrix[y * width + x] = matrix[(y + 1) * width + width - x - 1];
        }
    }
}

void LED::matrixBottom() {
    for (int i = 0; i < dotspos.size(); i++) {
        dotspos[i]++;
        if (dotspos[i] > (width - 1)) {
            dotspos[i] = 0;
        }
        if (ledstring.channel[0].strip_type == SK6812_STRIP_RGBW) {
            matrix[dotspos[i] + (height - 1) * width] = dotcolors_rgbw[i];
        } else {
            matrix[dotspos[i] + (height - 1) * width] = dotcolors[i];
        }
    }
}

void LED::setupHandlers() {
    struct sigaction sa = {
        .sa_handler = ctrlCHandler,
    };
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

void LED::ctrlCHandler(int signum) {
    (void)(signum);
    running = false;
}

int main(int argc, char *argv[]) {
    try {
        LED ledMatrix;
        ledMatrix.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
