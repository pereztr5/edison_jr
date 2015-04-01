/*
 * C file for the LED peripheral
 *
 * This peripheral actually creates a group of LEDs
 * instead of a single one.
 *
 * The bus has 32 bit size. We can decide how many
 * we are going to assign to the bus, when creating
 * an instance of this peripheral.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <miniat/miniat.h>
#include "led_block.h"
#include "SDL/edison_led_matrix.h"

struct led_block
{
	int connected;
	m_uword address;
	m_bus *bus;
};

/*
 * Function for creating a new LED block
 *
 * Allocates the memory space for the peripheral,
 *
 */

led_block *led_block_new(m_uword address)
{

	led_block *led = (led_block *)malloc(sizeof(led_block));
	
	if(led)
	{
		led -> bus = (m_bus *)malloc(sizeof(m_bus));
		
		if(!led -> bus)
		{
			free(led);
			led = NULL;
		}
		else
		{
			led -> address = address;
			led -> connected = 0;
		}
	}
	return led;
}

/*
 * Connects the LED block to the bus
 *
 *
 */

void led_block_bus_connector_set(led_block *led, m_bus *bus)
{

	if(led && bus)
	{
		
		if(!led -> connected)
		{
			free(led -> bus);
		}
		
		led -> bus = bus;
		led -> connected = 1;
	}
	return;
}

/*
 * Free's the LED block
 *
 * The command free simply does the opposite of memory allocation (free's memory location)
 *
 */

void led_block_free(led_block *led)
{
	if(led)
	{
		if(!led -> connected)
		{
			free(led -> bus);
		}
		free(led);
	}
	return;
}

/*
 * Updates the current state of the LED block
 *
 * This is where is must update the graphics
 *
 * If display is set (peripheral was created), then
 * set the data that's being passed through the bus
 * to generate the correct graphics.
 *
 */

void led_block_clock(led_block *led, edison_led_matrix *matrix)
{
	int state = 0;
	int xCenter, yCenter;
	int xTemp, yTemp;

	if(led)
	{
		// CURSOR X

		if((led -> bus -> req) && (led -> bus -> address == led -> address) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data < 32 && (int)led -> bus -> data >= 0)
			{
				edison_led_matrix_set_cursor_x(matrix, (int)led -> bus -> data);	
			}
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address)))
		{
			led -> bus -> ack = M_LOW;	
		}

		// CURSOR Y

		else if((led -> bus -> req) && (led -> bus -> address == led -> address + 1) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data < 16 && (int)led -> bus -> data >= 0)
			{
				edison_led_matrix_set_cursor_y(matrix, (int)led -> bus -> data);
			}
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address + 1)))
		{
			led -> bus -> ack = M_LOW;	
		}

		// LED COLOR

		else if((led -> bus -> req) && (led -> bus -> address == led -> address + 2) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data >= 1)
			{
				state = 1;
			}
			else
			{
				state = 0;
			}

			edison_led_matrix_set_state(matrix, state);
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address + 2)))
		{
			led -> bus -> ack = M_LOW;	
		}

		// CIRCLE

		else if((led -> bus -> req) && (led -> bus -> address == led -> address + 3) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data >= 1)
			{
				xCenter = edison_led_matrix_get_cursor_x(matrix);
				yCenter = edison_led_matrix_get_cursor_y(matrix);

				xTemp = xCenter;
				yTemp = yCenter;

				yTemp += 2;

				for(int i = 0; i < 8; i++)
				{
					if(xTemp < 32 && xTemp >= 0 && yTemp < 16 && yTemp >= 0)
					{
						edison_led_matrix_set_cursor_x(matrix, xTemp);
						edison_led_matrix_set_cursor_y(matrix, yTemp);
						edison_led_matrix_set_state(matrix, 1);
					}

					if(i == 0 || i == 1)
					{
						xTemp += 1;
						yTemp -= 1;
					}
					else if(i == 2 || i == 3)
					{
						xTemp -= 1;
						yTemp -= 1;
					}
					else if(i == 4 || i == 5)
					{
						xTemp -= 1;
						yTemp += 1;
					}
					else if(i == 6 || i == 7)
					{
						xTemp += 1;
						yTemp += 1;
					}
				}

			edison_led_matrix_set_cursor_x(matrix, xCenter);
			edison_led_matrix_set_cursor_y(matrix, yCenter);
			}
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address + 3)))
		{
			led -> bus -> ack = M_LOW;	
		}

		// SQUARE

		else if((led -> bus -> req) && (led -> bus -> address == led -> address + 4) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data >= 1)
			{
				xCenter = edison_led_matrix_get_cursor_x(matrix);
				yCenter = edison_led_matrix_get_cursor_y(matrix);

				xTemp = xCenter;
				yTemp = yCenter;

				yTemp += 2;
				xTemp -= 1;

				for(int i = 0; i < 16; i++)
				{
					edison_led_matrix_set_cursor_x(matrix, xTemp);
					edison_led_matrix_set_cursor_y(matrix, yTemp);
					edison_led_matrix_set_state(matrix, 1);
					
					if(i < 5)
					{
						xTemp += 1;
					}
					else if(i < 9)
					{
						yTemp -= 1;
					}
					else if(i < 13)
					{
						xTemp -= 1;
					}
					else
					{
						yTemp += 1;
					}
				}

			edison_led_matrix_set_cursor_x(matrix, xCenter);
			edison_led_matrix_set_cursor_y(matrix, yCenter);
			}
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address + 4)))
		{
			led -> bus -> ack = M_LOW;	
		}
	}
	return;
}

/*
 * Sets the LED block's bus
 *
 *
 *
 */

void led_block_set_bus(led_block *led, m_bus bus)
{
	if(led)
	{
		memcpy(led -> bus, &bus, sizeof(bus));
	}
	return;
}


