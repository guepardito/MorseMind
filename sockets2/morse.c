/*
 * newtest.c
 *
 * Copyright (c) 2014 Jeremy Garff <jer @ jers.net>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     1.  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *     3.  Neither the name of the owner nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

static char VERSION[] = "XX.YY.ZZ";

#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ws2811.h"
#include "morse.h"
#include "clk.h"
#include "dma.h"
#include "gpio.h"
#include "pwm.h"
#include "version.h"




#define ARRAY_SIZE(stuff) (sizeof(stuff) / sizeof(stuff[0]))

// defaults for cmdline options
#define TARGET_FREQ WS2811_TARGET_FREQ
#define GPIO_PIN 18
#define DMA 10
// #define STRIP_TYPE            WS2811_STRIP_RGB		//
// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE WS2811_STRIP_GBR // WS2812/SK6812RGB integrated chip+leds
// #define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW
// (NOT SK6812RGB)

#define WIDTH 8
#define HEIGHT 8
#define LED_COUNT (WIDTH * HEIGHT)


//MORSE
#include <unistd.h> // Para usleep()

// Define las luces de colores para el código Morse
#define DOT_COLOR 0x00200000 // Rojo
#define DASH_COLOR 0x000000FF // Azul


int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;

int clear_on_exit = 0;

//Ajustes basicos necesarios
ws2811_t ledstring = {
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
        {
            [0] =
                {
                    .gpionum = GPIO_PIN,
                    .invert = 0,
                    .count = LED_COUNT,
                    .strip_type = STRIP_TYPE,
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

ws2811_led_t *matrix;

static uint8_t running = 1;

//Inicializar matriz de led
void matrix_render(void) {
  int x, y;

  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
    }
  }
}

//Efecto visual arriba
void matrix_raise(void) {
  int x, y;

  for (y = 0; y < (height - 1); y++) {
    for (x = 0; x < width; x++) {
      // This is for the 8x8 Pimoroni Unicorn-HAT where the LEDS in subsequent
      // rows are arranged in opposite directions
      matrix[y * width + x] = matrix[(y + 1) * width + width - x - 1];
    }
  }
}


//Limpiar la matriz
void matrix_clear(void) {
  int x, y;

  for (y = 0; y < (height); y++) {
    for (x = 0; x < width; x++) {
      matrix[y * width + x] = 0;
    }
  }
}

//Establecer colores
int dotspos[] = {0, 1, 2, 3, 4, 5, 6, 7}; 
//0x01E3B00A, // azul
//0x0100B00A, // Verde
//0x000000FF //Rojo

ws2811_led_t dotcolors[] = {
    0x01E3B00A, // Azul
    0x0100B00A, // Verde
    0x0F0000FF, // Rojo
    0x00002000, // green
    0x00002020, // lightblue
    0x00000020, // blue
    0x00100010, // purple
    0x00200010, // pink
    0x01E3B00A, // azul
    0x0100B00A, // Verde
    0x000000FF //Rojo
};

ws2811_led_t dotcolors_rgbw[] = {
    0x00200000, // red
    0x10200000, // red + W
    0x00002000, // green
    0x10002000, // green + W
    0x00000020, // blue
    0x10000020, // blue + W
    0x00101010, // white
    0x10101010, // white + W

};

//Efecto visual abajo
void matrix_bottom(void) {
  int i;

  for (i = 0; i < (int)(ARRAY_SIZE(dotspos)); i++) {
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


//Garantiza que cuando el usuario presione Ctrl+C, el programa se detenga
static void ctrl_c_handler(int signum) {
  (void)(signum);
  running = 0;
}

//Manejar adecuadamente la terminación del programa.
static void setup_handlers(void) {
  struct sigaction sa = {
      .sa_handler = ctrl_c_handler,
  };

  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);
}

//Procesa los argumentos de línea de comandos y configura las opciones correspondientes en la estructura ws2811
void parseargs(int argc, char **argv, ws2811_t *ws2811) {
  int index;
  int c;

  static struct option longopts[] = {{"help", no_argument, 0, 'h'},
                                     {"dma", required_argument, 0, 'd'},
                                     {"gpio", required_argument, 0, 'g'},
                                     {"invert", no_argument, 0, 'i'},
                                     {"clear", no_argument, 0, 'c'},
                                     {"strip", required_argument, 0, 's'},
                                     {"height", required_argument, 0, 'y'},
                                     {"width", required_argument, 0, 'x'},
                                     {"version", no_argument, 0, 'v'},
                                     {0, 0, 0, 0}};

  while (1) {

    index = 0;
    c = getopt_long(argc, argv, "cd:g:his:vx:y:", longopts, &index);

    if (c == -1)
      break;

    switch (c) {
    case 0:
      /* handle flag options (array's 3rd field non-0) */
      break;

    case 'h':
      fprintf(stderr, "%s version %s\n", argv[0], VERSION);
      fprintf(stderr,
              "Usage: %s \n"
              "-h (--help)    - this information\n"
              "-s (--strip)   - strip type - rgb, grb, gbr, rgbw\n"
              "-x (--width)   - matrix width (default 8)\n"
              "-y (--height)  - matrix height (default 8)\n"
              "-d (--dma)     - dma channel to use (default 10)\n"
              "-g (--gpio)    - GPIO to use\n"
              "                 If omitted, default is 18 (PWM0)\n"
              "-i (--invert)  - invert pin output (pulse LOW)\n"
              "-c (--clear)   - clear matrix on exit.\n"
              "-v (--version) - version information\n",
              argv[0]);
      exit(-1);

    case 'D':
      break;

    case 'g':
      if (optarg) {
        int gpio = atoi(optarg);
        /*
                PWM0, which can be set to use GPIOs 12, 18, 40, and 52.
                Only 12 (pin 32) and 18 (pin 12) are available on the B+/2B/3B
                PWM1 which can be set to use GPIOs 13, 19, 41, 45 and 53.
                Only 13 is available on the B+/2B/PiZero/3B, on pin 33
                PCM_DOUT, which can be set to use GPIOs 21 and 31.
                Only 21 is available on the B+/2B/PiZero/3B, on pin 40.
                SPI0-MOSI is available on GPIOs 10 and 38.
                Only GPIO 10 is available on all models.

                The library checks if the specified gpio is available
                on the specific model (from model B rev 1 till 3B)

        */
        ws2811->channel[0].gpionum = gpio;
      }
      break;

    case 'i':
      ws2811->channel[0].invert = 1;
      break;

    case 'c':
      clear_on_exit = 1;
      break;

    case 'd':
      if (optarg) {
        int dma = atoi(optarg);
        if (dma < 14) {
          ws2811->dmanum = dma;
        } else {
          printf("invalid dma %d\n", dma);
          exit(-1);
        }
      }
      break;

    case 'y':
      if (optarg) {
        height = atoi(optarg);
        if (height > 0) {
          ws2811->channel[0].count = height * width;
        } else {
          printf("invalid height %d\n", height);
          exit(-1);
        }
      }
      break;

    case 'x':
      if (optarg) {
        width = atoi(optarg);
        if (width > 0) {
          ws2811->channel[0].count = height * width;
        } else {
          printf("invalid width %d\n", width);
          exit(-1);
        }
      }
      break;

    case 's':
      if (optarg) {
        if (!strncasecmp("rgb", optarg, 4)) {
          ws2811->channel[0].strip_type = WS2811_STRIP_RGB;
        } else if (!strncasecmp("rbg", optarg, 4)) {
          ws2811->channel[0].strip_type = WS2811_STRIP_RBG;
        } else if (!strncasecmp("grb", optarg, 4)) {
          ws2811->channel[0].strip_type = WS2811_STRIP_GRB;
        } else if (!strncasecmp("gbr", optarg, 4)) {
          ws2811->channel[0].strip_type = WS2811_STRIP_GBR;
        } else if (!strncasecmp("brg", optarg, 4)) {
          ws2811->channel[0].strip_type = WS2811_STRIP_BRG;
        } else if (!strncasecmp("bgr", optarg, 4)) {
          ws2811->channel[0].strip_type = WS2811_STRIP_BGR;
        } else if (!strncasecmp("rgbw", optarg, 4)) {
          ws2811->channel[0].strip_type = SK6812_STRIP_RGBW;
        } else if (!strncasecmp("grbw", optarg, 4)) {
          ws2811->channel[0].strip_type = SK6812_STRIP_GRBW;
        } else {
          printf("invalid strip %s\n", optarg);
          exit(-1);
        }
      }
      break;

    case 'v':
      fprintf(stderr, "%s version %s\n", argv[0], VERSION);
      exit(-1);

    case '?':
      /* getopt_long already reported error? */
      exit(-1);

    default:
      exit(-1);
    }
  }
}

//Morse
//---------------

//Enciende . y - con espacio
void display_morse_string(const char* morse_string) {
    int position = 0; // Posición inicial en la matriz

    matrix_clear(); // Limpiar la matriz al inicio

    // Iterar a través de cada carácter en la cadena de caracteres Morse
    for (int i = 0; morse_string[i] != '\0'; i++) {
        char c = morse_string[i];

        switch (c) {
            case '.':
                // Enciende una LED en rojo para un punto
                matrix[position] = dotcolors[0]; // Azul
                position++;
                break;
            case '-':
                // Enciende dos LEDs en naranja para un guion
                matrix[position] = dotcolors[0]; // Azul
                position++;
                matrix[position] = dotcolors[0]; // Azul
                position++;
                break;
            case ' ':
                // Deja un espacio (LED apagada)
                position++;
                break;
            default:
                // Ignora caracteres no reconocidos
                break;
        }

        // Inserta un espacio entre cada símbolo
        position++;
    }

    // Renderizamos los cambios
    ws2811_render(&ledstring);
}

void display_ganar() {
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            // Enciende cada LED en verde
            matrix[y * width + x] = dotcolors[1]; // Color verde
        }
    }
}

void display_perder() {
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            // Enciende cada LED en rojo
            matrix[y * width + x] = dotcolors[2]; // Color rojo
        }
    }
}



//main
//int main(int argc, char *argv[]) {
    /*ws2811_return_t ret;

    sprintf(VERSION, "%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO);

    parseargs(argc, argv, &ledstring);

    matrix = malloc(sizeof(ws2811_led_t) * width * height);

    setup_handlers();

    //Asegura que la biblioteca ws2811, que se encarga de controlar los LEDs
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }
    const char* morse_string = "-.. -- -.";
    while (running) {
        //display_ganar(); //FUNCIONA
        //display_perder(); //FUNCIONA
        //display_morse_string(morse_string); //FUNCIONA
        matrix_render();


        if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_render failed: %s\n",
                ws2811_get_return_t_str(ret));
        break;
        }

        // 15 frames /sec
        usleep(1000000 / 15);
    }

    if (clear_on_exit) {
        matrix_clear();
        matrix_render();
        ws2811_render(&ledstring);
    }

    ws2811_fini(&ledstring);

    printf("\n");
    return ret;*/
//}