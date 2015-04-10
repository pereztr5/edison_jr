/*
 * Header file for the LCD display peripheral
 *
 *
 */

#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_

#include "miniat/miniat.h"
#include "SDL/edison_lcd_display.h"

#define NUMBER_LINES 5
#define CHARS_PER_LINE 20

typedef struct lcd_display lcd_display;

/*
 * Creates a new LCD display peripheral, setting it's address
 * to "address" for the miniAT
 *
 *
 *
 */

extern lcd_display *lcd_display_new(m_uword address);

/*
 * Free's the memory address for the LCD display passed
 * as argument
 *
 *
 *
 */

extern void lcd_display_free(lcd_display *lcd);

/*
 * Clock function
 *
 * This will update the current value for the LCD display
 *
 *
 */

extern void lcd_display_clock(lcd_display *lcd, edison_lcd_display *edison_lcd);

/*
 * Tries to connect the LCD display with the bus
 *
 *
 *
 *
 */

extern void lcd_display_bus_connector_set(lcd_display *lcd, m_bus *bus);

/*
 * Sets the LCD display's bus
 *
 *
 *
 *
 */

extern m_bus lcd_display_get_bus(lcd_display *lcd);

#endif 