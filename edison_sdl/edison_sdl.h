#ifndef _EDISON_SDL_H_
#include "/usr/include/SDL2/SDL.h"
#include <stdbool.h>
#include "edison_led.h"

#ifndef _DEF_UINT_
#define _DEF_UINT_
typedef unsigned int uint;
#endif

/**
 * 
 */
/**
 * Contains state information for the Edison Jr. board.
 * \param led_list An array of LEDs added to the board.
 * \param switch_list An array of switches added to the board.
 * \param board_size The size of the drawn window, in pixels.
 */
typedef struct edison_board
{
	edison_led* led_list[100];
	uint led_count;
	//edison_switch* switch_list[100];
	//uint switch_count;
	SDL_Point board_size;
	SDL_Window* window;
	SDL_Surface* board_surface
;} edison_board;


/**
 * Creates a new instance of the Edison Jr.
 * \returns Pointer to an initialized Edison Jr. board.
 */
edison_board* edison_create_board(uint size_x, uint size_y);

/**
 * Destroys the given Edison Jr. board.
 * \param board The Edison Jr. board to destroy.
 */
void edison_destroy_board(edison_board* board);

/**
 * Polls for events, handling clicking of switches and buttons
 * \returns void
 */
void edison_poll_events();

/**
 * Render the Edison Jr. board.
 * \param board The Edison Jr. board to render
 * \returns void
 */
void edison_render(edison_board* board);

/**
 * Adds an LED to the Edison Jr. board.
 * \param board The Edison Jr. board we are adding to.
 * \param led The LED to add to the board.
 * \returns void
 */
void edison_add_led(edison_board* board, edison_led* led);

/**
 * Gets a given instance of a LED.
 * \param id The unique ID of the LED to look for.
 * \returns A pointer to the desired LED, or NULL if it doesn't exist.
 */
edison_led* edison_get_led(edison_board* board, uint id);

/**
 * Renders all LEDs on the board
 * \param board The Edison Jr board to render to.
 * \returns void
 */
 void edison_render_leds(edison_board* board);


#define _EDISON_SDL_H_
#endif