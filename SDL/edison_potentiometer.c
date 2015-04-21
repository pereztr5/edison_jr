/*
 * Potentiometer SDL
 *
 * 
 *
 */

#include <stdlib.h>
#include "edison_potentiometer.h"

edison_potentiometer* edison_create_potentiometer(void)
{
	edison_potentiometer* edison_pot = malloc(sizeof(edison_potentiometer));

	edison_pot -> current_position = 10;

	edison_pot -> hitbox.w = 20;
	edison_pot -> hitbox.h = 20;
	edison_pot -> hitbox.x = 30;
	edison_pot -> hitbox.y = 280;

	edison_pot -> potentiometer_mode = 0;

	return edison_pot;
}

void edison_potentiometer_set_pos(edison_potentiometer* edison_pot, int position)
{
	edison_pot -> current_position = position;
	return;
}

int edison_potentiometer_get_pos(edison_potentiometer* edison_pot)
{
	int pos;

	pos = edison_pot -> current_position;

	return (11 - pos);
}

