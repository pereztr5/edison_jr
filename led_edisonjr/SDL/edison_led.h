#ifndef _EDISON_LED_H_
#include "/usr/local/include/SDL2/SDL.h"
#include <stdbool.h>
#include "edison_util.h"

/**
 * Contains state information for LEDs
 */
typedef struct edison_led
{
	uint id;
	bool state;
	SDL_Color color;
	SDL_Point position;
}edison_led;

/**
 * Creates a new instance of an LED for use.
 * \returns Pointer to an initialized LED.
 */
edison_led* edison_create_led(int pos_x, int pos_y, uint r, uint g, uint b);

/**
 * Sets the state of a given LED.
 * \param led The LED we are altering.
 * \param state The state we want to set it to - true for on, false for off.
 * \returns void
 */
void edison_led_set_state(edison_led* led, bool state);

/**
 * Sets the position of a given LED.
 * \param led The LED we are altering.
 * \param pos_x The horizontal position to move the LED to, (0, 0) is the upper left corner of the window
 * \param pos_y The vertical position to move the LED to, (0, 0) is the upper left corner of the window
 * \returns void
 */
void edison_led_set_position(edison_led* led, int pos_x, int pos_y);

/**
 * Sets the color of a given LED.
 * \param led The LED we are altering.
 * \param r The red value to set the LED color to.
 * \param g The green value to set the LED color to.
 * \param b The blue value to set the LED color to.
 * \returns void
 */
void edison_led_set_color(edison_led* led, uint r, uint g, uint b);

/**
 * 
 */
void edison_led_set_id(edison_led* led, uint id);

#define _EDISON_LED_H_
#endif