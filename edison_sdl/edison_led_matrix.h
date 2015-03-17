#include "edison_util.h"
#include "edison_led.h"

typedef struct edison_led_matrix edison_led_matrix;

edison_led_matrix* edison_create_led_matrix(uint pos_x, uint pos_y, uint size_x, uint size_y, uint padding, uint r, uint g, uint b);

uint edison_led_matrix_get_cursor_x(edison_led_matrix* mat);

uint edison_led_matrix_get_cursor_y(edison_led_matrix* mat);

void edison_led_matrix_set_cursor_x(edison_led_matrix* mat, uint new_x);

void edison_led_matrix_set_cursor_y(edison_led_matrix* mat, uint new_y);

void edison_led_matrix_set_state(edison_led_matrix* mat, bool state);

bool edison_led_matrix_get_state(edison_led_matrix* mat);

void edison_led_matrix_set_color(edison_led_matrix* mat, uint r, uint g, uint b);