#ifndef _EDISON_SDL_H_
#include "/usr/local/include/SDL2/SDL.h"
#include <stdbool.h>
#include <stdlib.h>
#include "edison_util.h"
#include "edison_led.h"
#include "edison_button.h"
#include "edison_led_matrix.h"
#include "edison_seven_segment.h"
#include "edison_dipswitch.h"

/**
 * Contains state information for the Edison Jr. board.
 * \param led_list An array of LEDs added to the board.
 * \param switch_list An array of switches added to the board.
 * \param board_size The
  size of the drawn window, in pixels.
 */
typedef struct edison_board edison_board;


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
 * \param board The Edison Jr. board to check for events
 * \returns void
 */
bool edison_poll_events(edison_board* board);

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

/**
 * Adds a button to the Edison Jr. board.
 * \param board The Edison Jr. board we are adding to.
 * \param button The button to add to the board.
 * \returns void
 */
void edison_add_button(edison_board* board, edison_button* button);

/**
 * Gets a given instance of a button.
 * \param id The unique ID of the button to look for.
 * \returns A pointer to the desired button, or NULL if it doesn't exist.
 */
edison_button* edison_get_button(edison_board* baord, uint id);

/**
 * Renders all buttons on the board
 * \param board The Edison Jr board to render to.
 * \returns void
 */
void edison_render_buttons(edison_board* board);

/**
 * Adds an LED matrix to the Edison Jr. board.
 * \param board The Edison Jr. board we are adding to.
 * \param button The matrix to add to the board.
 * \returns void
 */
void edison_add_led_matrix(edison_board* board, edison_led_matrix* mat);

/**
 * Adds a seven segment display to the Edison Jr. board.
 * \param board The Edison Jr. board we are adding to.
 * \param sevenseg The seven segment display to add to the board.
 * \returns void
 */
void edison_add_sevenseg(edison_board* board, edison_sevenseg* sevenseg);

/**
 * Gets an instance of a seven segment display.
 * \param board The Edison Jr. board the seven segment display is on
 * \param id The unique ID of the seven segment display to look for.
 * \returns A pointer to the desired seven segment display, or NULL if it doesn't exist.
 */
edison_sevenseg* edison_get_sevenseg(edison_board* board, uint id);

/**
 * Renders all seven segment displays on the board
 * \param board The Edison Jr. board to render to.
 * \returns void
 */
void edison_render_sevensegs(edison_board* board);

/**
 * Adds a dipswitch to the Edison Jr. board.
 * \param board The Edison Jr. board we are adding to.
 * \param dipswitch The seven dipswitch to add to the board.
 * \returns void
 */
void edison_add_dipswitch(edison_board* board, edison_dipswitch* dipswitch);

/**
 * Gets an instance of a dipswitch.
 * \param board The Edison Jr. board the dipswitch is on
 * \param id The unique ID of the dipswitch to look for.
 * \returns A pointer to the desired dipswitch, or NULL if it doesn't exist.
 */
edison_dipswitch* edison_get_dipswitch(edison_board* board, uint id);

/**
 * Renders all dipswitches on the board
 * \param board The Edison Jr. board to render to.
 * \returns void
 */
void edison_render_dipswitches(edison_board* board);

#define _EDISON_SDL_H_
#endif