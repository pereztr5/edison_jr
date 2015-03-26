#ifndef _EDISON_BUTTON_H_
#define _EDISON_BUTTON_H_
#include "/usr/local/include/SDL2/SDL.h"
#include <stdbool.h>
#include "edison_util.h"

typedef struct edison_button
{
	uint id;
	bool pressed;
	SDL_Rect hitbox;

} edison_button;

edison_button* edison_create_button(int pos_x, int pos_y, uint width, uint height);
void edison_button_set_position(edison_button* button, int pos_x, int pos_y);
void edison_button_set_size(edison_button* button, uint width, uint height);
void edison_button_set_state(edison_button* button, bool pressed);
bool edison_button_get_state(edison_button* button);

#endif