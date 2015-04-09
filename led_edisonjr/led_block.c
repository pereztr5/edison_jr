/*
 * C file for the LED peripheral
 *
 * Creates a matrix of LEDs (32x16)
 *
 */

// Libs

#include <stdlib.h>
#include <string.h>
#include <math.h>

// Headers

#include <miniat/miniat.h>
#include "led_block.h"
#include "SDL/edison_led_matrix.h"

// Important Numbers

#define MATRIX_X_SIZE	32
#define MATRIX_Y_SIZE	16

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
 * This function has 5 memory addresses for the assembly programmer
 *
 * 		CURSORX  : 0x4000
 * 		CURSORY  : 0X4001
 * 		LEDCOLOR : 0X4002
 *		CIRCLE	 : 0X4003
 *		SQUARE	 : 0X4004
 *
 *	Variables
 *
 *		state   : State of the led being pointed by the cursor
 *		xCenter : center for circle and square
 *		yCenter : center for circle and square
 *		xTemp	: temporary X for drawing circle and square
 *		yTemp	: temporary Y for drawing circle and square
 */

void led_block_clock(led_block *led, edison_led_matrix *matrix)
{
	int state = 0;
	int xCenter, yCenter;
	int xTemp, yTemp;

	if(led)
	{
		// 0x4000 - CURSOR X

		if((led -> bus -> req) && (led -> bus -> address == led -> address) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data < MATRIX_X_SIZE && (int)led -> bus -> data >= 0)
			{
				edison_led_matrix_set_cursor_x(matrix, (int)led -> bus -> data);	
			}
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address)))
		{
			led -> bus -> ack = M_LOW;	
		}

		// 0x4001 - CURSOR Y

		else if((led -> bus -> req) && (led -> bus -> address == led -> address + 1) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data < MATRIX_Y_SIZE && (int)led -> bus -> data >= 0)
			{
				edison_led_matrix_set_cursor_y(matrix, (int)led -> bus -> data);
			}
		}
		else if(led -> bus -> ack && ((led -> bus -> address == led -> address + 1)))
		{
			led -> bus -> ack = M_LOW;	
		}

		// 0x4002 - LED COLOR

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

		// 0x4003 - CIRCLE

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
					if(xTemp < MATRIX_X_SIZE && xTemp >= 0 && yTemp < MATRIX_Y_SIZE && yTemp >= 0)
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

		// 0x4004 - SQUARE

		else if((led -> bus -> req) && (led -> bus -> address == led -> address + 4) && (!led -> bus -> ack))
		{
			led -> bus -> ack = M_HIGH;

			if((int)led -> bus -> data >= 1)
			{
				xCenter = edison_led_matrix_get_cursor_x(matrix);
				yCenter = edison_led_matrix_get_cursor_y(matrix);

				xTemp = xCenter - 2;
				yTemp = yCenter - 2;

				for(int i = 0; i < 16; i++)
				{
					edison_led_matrix_set_cursor_x(matrix, xTemp);
					edison_led_matrix_set_cursor_y(matrix, yTemp);
					edison_led_matrix_set_state(matrix, 1);
					
					if(i < 4)
					{
						xTemp += 1;
					}
					else if(i < 8)
					{
						yTemp += 1;
					}
					else if(i < 12)
					{
						xTemp -= 1;
					}
					else
					{
						yTemp -= 1;
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


