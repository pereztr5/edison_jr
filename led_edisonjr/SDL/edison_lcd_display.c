/*
 * LCD Display SDL
 *
 * 
 *
 */

#include "edison_lcd_display.h"

edison_lcd_display* edison_create_lcd_display(void)
{
	edison_lcd_display* lcd = malloc(sizeof(edison_lcd_display));

	lcd -> cursor_pos_x = 0;
	lcd -> cursor_pos_y = 0;

	return lcd;
}

uint edison_lcd_display_get_cursor_x(edison_lcd_display* lcd)
{
	return lcd -> cursor_pos_x;
}

uint edison_lcd_display_get_cursor_y(edison_lcd_display* lcd)
{
	return lcd -> cursor_pos_y;
}

void edison_lcd_display_set_cursor_x(edison_lcd_display* lcd, uint new_x)
{
	if(new_x < MAX_CHARS)
	{
		lcd -> cursor_pos_x = new_x;
	}

	return;
}

void edison_lcd_display_set_cursor_y(edison_lcd_display* lcd, uint new_y)
{
	if(new_y < MAX_LINES)
	{
		lcd -> cursor_pos_y = new_y;
	}

	return;
}

void edison_lcd_display_set_char(edison_lcd_display* lcd, char character)
{
	lcd -> display_content[(MAX_CHARS) * (lcd -> cursor_pos_y) + lcd -> cursor_pos_x] = character;

	return;
}

char edison_lcd_display_get_char(edison_lcd_display* lcd)
{
	return lcd -> display_content[(MAX_CHARS) * (lcd -> cursor_pos_y) + lcd -> cursor_pos_x];
}
