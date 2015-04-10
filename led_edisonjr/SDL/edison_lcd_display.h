/*
 * LCD Display SDL
 *
 * 
 *
 */

#include "edison_util.h"

#ifndef __LCD__DISPLAY__H__
#define __LCD__DISPLAY__H__

#define MAX_LINES   5
#define MAX_CHARS  20

typedef struct edison_lcd_display
{
	char display_content[MAX_LINES * MAX_CHARS];
	uint cursor_pos_x;
	uint cursor_pos_y;

}edison_lcd_display;

edison_lcd_display* edison_create_lcd_display(void);

uint edison_lcd_display_get_cursor_x(edison_lcd_display* edison_lcd);

uint edison_lcd_display_get_cursor_y(edison_lcd_display* edison_lcd);

void edison_lcd_display_set_cursor_x(edison_lcd_display* edison_lcd, uint new_x);

void edison_lcd_display_set_cursor_y(edison_lcd_display* edison_lcd, uint new_y);

void edison_lcd_display_set_char(edison_lcd_display* edison_lcd, char character);

char edison_lcd_display_get_char(edison_lcd_display* edison_lcd);

#endif