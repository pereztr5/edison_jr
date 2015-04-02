#ifndef _EDISON_DIPSWITCH_H_
#include "/usr/include/SDL2/SDL.h"
#endif

#ifndef _DEF_UINT_
#define _DEF_UINT_
typedef unsigned int uint;
#endif

/**
 * Contains state information for the dipswitch
 */
typedef struct edison_dipswitch edison_dipswitch;

/**
 * Creates a new instance of a dipswitch.
 * \param pos_x The x position of the created dipswitch
 * \param pos_y The y position of the created dipswitch
 * \param width The width of the entire dipswitch
 * \param height The height of the entire dipswitch
 * \returns Pointer to an initialized dipswitch
 */
edison_dipswitch* edison_create_dipswitch(int pos_x, int pos_y, int width, int height);

/**
 * Sets the state of a given dipswitch
 * \param dipswitch The dipswitch we're altering
 * \param state The state of the dipswitch
 * \returns void
 */
void edison_dipswitch_set_state(edison_dipswitch* dipswitch, int* state);

/*
 * Gets the states of all the switches in the DIP Switch 
 * 
 * Returns an array
 * 
 */

int* edison_dipswitch_get_state(edison_dipswitch* dipswitch);