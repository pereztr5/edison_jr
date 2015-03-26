#include "edison_led.h"

/*

struct edison_led
{
	uint id;
	bool state;
	SDL_Color color;
	SDL_Point position;
};

*/

edison_led* edison_create_led(int pos_x, int pos_y, uint r, uint g, uint b)
{
	edison_led* led = malloc(sizeof(edison_led));
	edison_led_set_state(led, 0);
	edison_led_set_position(led, pos_x, pos_y);
	edison_led_set_color(led, r, g, b);
	return led;
}

void edison_led_set_state(edison_led* led, bool state)
{
	led->state = state;
}

void edison_led_set_position(edison_led* led, int pos_x, int pos_y)
{
	SDL_Point new_pos;
	new_pos.x = pos_x;
	new_pos.y = pos_y;
	led->position = new_pos;
}

void edison_led_set_color(edison_led* led, uint r, uint g, uint b)
{
	SDL_Color new_color;
	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	led->color = new_color;
}

void edison_led_set_id(edison_led* led, uint id)
{
	led->id = id;
}