/*
 * Potentiometer SDL
 *
 * 
 *
 */

#ifndef __POTENTIOMETER__H__
#define __POTENTIOMETER__H__

#include "SDL.h"

typedef struct edison_potentiometer
{
	int potentiometer_mode;
	int current_position;
	SDL_Rect hitbox;

}edison_potentiometer;

edison_potentiometer* edison_create_potentiometer(void);

void edison_potentiometer_set_pos(edison_potentiometer* edison_pot, int position);

int edison_potentiometer_get_pos(edison_potentiometer* edison_pot);

#endif
