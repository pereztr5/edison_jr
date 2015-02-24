#ifndef _EDISON_SWITCH_H_
#include "SDL/SDL2.h"
#include <stdbool.h>

/**
 * Contains state information for switches
 */
typedef struct edison_switch
{
	bool state;
	SDL_Point position;
} edison_switch;

/**
 * Creates a new instance of an switch for use
 * \returns Pointer to an uninitialized switch.
 */
edison_switch* edison_create_switch();

/**
 * Sets the state of a given switch
 * \param switch The switch we are altering.
 * \param state The state we want to set it to - true for on, false for off.
 * \returns void
 */
void edison_switch_set_state(edison_switch* switch, bool state);

/**
 * Sets the position of a given switch
 * \param switch The switch we are altering.
 * \param new_pos the new position of the switch.
 * \returns void
 */
void edison_switch_set_position(edison_switch* switch, int pos_x, int pos_y);


#define _EDISON_SWITCH_H_
#endif