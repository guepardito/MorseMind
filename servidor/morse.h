#ifndef HOLA_LED
#define HOLA_LED
// Variables globales
//int width;
//int height;
//int led_count;
//int clear_on_exit;
//ws2811_t ledstring;
// ws2811_led_t *matrix;
// uint8_t running;

extern "C"{
//Declaraciones de funciones
void matrix_render();
void matrix_raise(void);
void matrix_clear(void);
void matrix_bottom(void);
void parseargs(int argc, char **argv, ws2811_t *ws2811);
void display_morse_string(const char* morse_string);
void display_ganar();
void display_perder();
void display_apagar();
}

#endif

