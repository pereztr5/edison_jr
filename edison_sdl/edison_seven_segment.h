#ifndef _EDISON_SEVEN_SEGMENT_H_
#include "/usr/include/SDL2/SDL.h"

#ifndef _DEF_UINT_
#define _DEF_UINT_
typedef unsigned int uint;
#endif

/**
 * Contains state information for seven segment display
 */
typedef struct edison_sevenseg
{
	uint id;
	const struct SDL_Rect segs[8];
	int status[8];
} edison_sevenseg;

/**
 * Creates a new instance of a seven segment display.
 * \param pos_x The x position of the created seven segment display
 * \param pos_y The y position of the created seven segment display
 * \param width The width of the top segment
 * \param height The height of the top segment
 * \returns Pointer to an initialized seven segment display
 */
edison_sevenseg* edison_create_sevenseg(int pos_x, int pos_y, int width, int height);

/**
 * Sets the state of a given seven segment display
 * \param led The LED we are altering.
 * \param state The states of each segment in the display.
 * \returns void
 */
void edison_sevenseg_set_state(edison_sevenseg* sevenseg, int state[8]);
