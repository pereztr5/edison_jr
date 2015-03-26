#ifndef __LED__MATRIX__H__
#include "edison_util.h"
#include "edison_led.h"


typedef struct edison_led_matrix
{
	edison_led* led_grid[EDISON_LED_GRID_MAX];
	uint led_count_x;
	uint led_count_y;
	uint cursor_pos_x;
	uint cursor_pos_y;
}edison_led_matrix;

edison_led_matrix* edison_create_led_matrix(uint pos_x, uint pos_y, uint size_x, uint size_y, uint padding, uint r, uint g, uint b);

uint edison_led_matrix_get_cursor_x(edison_led_matrix* mat);

uint edison_led_matrix_get_cursor_y(edison_led_matrix* mat);

void edison_led_matrix_set_cursor_x(edison_led_matrix* mat, uint new_x);

void edison_led_matrix_set_cursor_y(edison_led_matrix* mat, uint new_y);

void edison_led_matrix_set_state(edison_led_matrix* mat, bool state);

bool edison_led_matrix_get_state(edison_led_matrix* mat);

void edison_led_matrix_set_color(edison_led_matrix* mat, uint r, uint g, uint b);

#define __LED__MATRIX__H__
#endif