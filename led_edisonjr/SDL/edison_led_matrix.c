#include "edison_led_matrix.h"

/*
struct edison_led_matrix
{
	edison_led* led_grid[EDISON_LED_GRID_MAX];
	uint led_count_x;
	uint led_count_y;
	uint cursor_pos_x;
	uint cursor_pos_y;
};
*/	

edison_led_matrix* edison_create_led_matrix(uint pos_x, uint pos_y, uint size_x, uint size_y, uint padding, uint r, uint g, uint b)
{
	edison_led_matrix* mat = malloc(sizeof(edison_led_matrix));
	mat->led_count_x = size_x;
	mat->led_count_y = size_y;
	mat->cursor_pos_x = 0;
	mat->cursor_pos_y = 0;

	uint i = 0, j = 0;

	uint px = pos_x;
	uint py = pos_y;
	for(; i < size_y; i++)
	{
		py = pos_y;
		for(j = 0; j < size_x; j++)
		{
			edison_led* led = edison_create_led(py, px, r, g , b);
			mat->led_grid[size_x * i + j] = led;
			//printf("Creating LED at (%d, %d)\n", j, i);
			py += EDISON_LED_SIZE + padding;
		}
		px += EDISON_LED_SIZE + padding;
	}

	return mat;
}

uint edison_led_matrix_get_cursor_x(edison_led_matrix* mat)
{
	return mat->cursor_pos_x;
}

uint edison_led_matrix_get_cursor_y(edison_led_matrix* mat)
{
	return mat->cursor_pos_y;
}

void edison_led_matrix_set_cursor_x(edison_led_matrix* mat, uint new_x)
{
	if(new_x < mat->led_count_x)
		mat->cursor_pos_x = new_x;
}

void edison_led_matrix_set_cursor_y(edison_led_matrix* mat, uint new_y)
{
	if(new_y < mat->led_count_y)
		mat->cursor_pos_y = new_y;
}

void edison_led_matrix_set_state(edison_led_matrix* mat, bool state)
{
	mat->led_grid[(mat->led_count_x) * (mat->cursor_pos_y) + mat->cursor_pos_x]->state = state;
}

bool edison_led_matrix_get_state(edison_led_matrix* mat)
{
	return mat->led_grid[(mat->led_count_x) * (mat->cursor_pos_y) + mat->cursor_pos_x]->state;
}


void edison_led_matrix_set_color(edison_led_matrix* mat, uint r, uint g, uint b)
{
	SDL_Color c = {r, g, b};
	mat->led_grid[(mat->led_count_x) * (mat->cursor_pos_y) + mat->cursor_pos_x]->color = c;
}