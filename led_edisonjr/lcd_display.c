/*
 * C file for the LCD display peripheral
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <miniat/miniat.h>
#include "lcd_display.h"

struct lcd_display
{
	int connected;
	m_uword address;
	m_bus *bus;
};

/*
 * Function for creating a new LCD display
 *
 * Allocates the memory space for the peripheral,
 *
 */

lcd_display *lcd_display_new(m_uword address)
{

	lcd_display *lcd = (lcd_display *)malloc(sizeof(lcd_display));
	
	if(lcd)
	{
		lcd -> bus = (m_bus *)malloc(sizeof(m_bus));
		
		if(!lcd -> bus)
		{
			free(lcd);
			lcd = NULL;
		}
		else
		{
			lcd -> address = address;
			lcd -> connected = 0;
		}
	}
	return lcd;
}

/*
 * Connects the LCD display to the bus
 *
 *
 */

void lcd_display_bus_connector_set(lcd_display *lcd, m_bus *bus)
{

	if(lcd && bus)
	{
		
		if(!lcd -> connected)
		{
			free(lcd -> bus);
		}
		
		lcd -> bus = bus;
		lcd -> connected = 1;
	}
	return;
}

/*
 * Free's the LCD display
 *
 * The command free simply does the opposite of memory allocation (free's memory location)
 *
 */

void lcd_display_free(lcd_display *lcd)
{
	if(lcd)
	{
		if(!lcd -> connected)
		{
			free(lcd -> bus);
		}
		free(lcd);
	}
	return;
}

/*
 * LCD clock
 *
 * Updates the display with the information sent
 *
 */

void lcd_display_clock(lcd_display *lcd)
{
	if(lcd)
	{
		// 0x4040 - CURSOR X

		if((lcd -> bus -> req) && (lcd -> bus -> address == lcd -> address) && (!lcd -> bus -> ack))
		{
			lcd -> bus -> ack = M_HIGH;

			if((int)lcd -> bus -> data >= 0 && (int)lcd -> bus -> data < CHARS_PER_LINE)
			{
				// SET CURSOR X SDL FUNCTION
			}
			
		}
		else if(lcd -> bus -> ack && ((lcd -> bus -> address == lcd -> address)))
		{
			lcd -> bus -> ack = M_LOW;	
		}

		// 0x4041 - CURSOR Y

		else if((lcd -> bus -> req) && (lcd -> bus -> address == lcd -> address + 1) && (!lcd -> bus -> ack))
		{
			lcd -> bus -> ack = M_HIGH;

			if((int)lcd -> bus -> data >= 0 && (int)lcd -> bus -> data < NUMBER_LINES)
			{
				// SET CURSOR Y SDL FUNCTION
			}
			
		}
		else if(lcd -> bus -> ack && ((lcd -> bus -> address == lcd -> address + 1)))
		{
			lcd -> bus -> ack = M_LOW;	
		}

		// 0x4042 - WRITING

		else if((lcd -> bus -> req) && (lcd -> bus -> address == lcd -> address + 2) && (!lcd -> bus -> ack))
		{
			lcd -> bus -> ack = M_HIGH;

			// edison_sdl_write_display(edison_lcd, (char) lcd -> bus -> data);
			
		}
		else if(lcd -> bus -> ack && ((lcd -> bus -> address == lcd -> address + 2)))
		{
			lcd -> bus -> ack = M_LOW;	
		}

	}
	return;
}

/*
 * Gets the LCD display's bus
 *
 *
 *
 */

m_bus lcd_display_get_bus(lcd_display *lcd)
{
	m_bus bus = { 0 };
	if(!lcd)
	{
		return bus;
	}
	return *(lcd -> bus);
}
