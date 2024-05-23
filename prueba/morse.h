#ifndef _MORSE_H_
#define _MORSE_H_

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

#include "clk.h"
#include "dma.h"
#include "gpio.h"
#include "pwm.h"
#include "version.h"
#include "ws2811.h"

// Definiciones y macros
#define ARRAY_SIZE(stuff) (sizeof(stuff) / sizeof(stuff[0]))

// defaults for cmdline options
#define TARGET_FREQ WS2811_TARGET_FREQ
#define GPIO_PIN 18
#define DMA 10
#define STRIP_TYPE WS2811_STRIP_GBR // WS2812/SK6812RGB integrated chip+leds

#define WIDTH 8
#define HEIGHT 8
#define LED_COUNT (WIDTH * HEIGHT)

// Colores para el código Morse
#define DOT_COLOR 0x00200000  // Rojo
#define DASH_COLOR 0x000000FF // Azul

// Variables globales
extern int width;
extern int height;
extern int led_count;
extern int clear_on_exit;
extern ws2811_t ledstring;
extern ws2811_led_t *matrix;
extern uint8_t running;

// Declaraciones de funciones
void matrix_render(void);
void matrix_raise(void);
void matrix_clear(void);
void matrix_bottom(void);
void parseargs(int argc, char **argv, ws2811_t *ws2811);
void display_morse_string(const char* morse_string);
void display_ganar(void);
void display_perder(void);

#endif // _MORSE_H_
