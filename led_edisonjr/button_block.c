/*
 * C file for the Button Block peripheral
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <miniat/miniat.h>
#include "button_block.h"

struct button_block
{
	int connected;
	m_uword address;
	m_bus *bus;
};

/*
 * Function for creating a new Button block
 *
 * Allocates the memory space for the peripheral,
 *
 */

button_block *button_block_new(m_uword address)
{

	button_block *buttons = (button_block *)malloc(sizeof(button_block));
	
	if(buttons)
	{
		buttons -> bus = (m_bus *)malloc(sizeof(m_bus));
		
		if(!buttons -> bus)
		{
			free(buttons);
			buttons = NULL;
		}
		else
		{
			buttons -> address = address;
			buttons -> connected = 0;
		}
	}
	return buttons;
}

/*
 * Connects the Button block to the bus
 *
 *
 */

void button_block_bus_connector_set(button_block *buttons, m_bus *bus)
{

	if(buttons && bus)
	{
		
		if(!buttons -> connected)
		{
			free(buttons -> bus);
		}
		
		buttons -> bus = bus;
		buttons -> connected = 1;
	}
	return;
}

/*
 * Free's the Button block
 *
 * The command free simply does the opposite of memory allocation (free's memory location)
 *
 */

void button_block_free(button_block *buttons)
{
	if(buttons)
	{
		if(!buttons -> connected)
		{
			free(buttons -> bus);
		}
		free(buttons);
	}
	return;
}

/*
 * Reads the states of the buttons to update the bus and the SDL
 *
 *
 *
 */

void button_block_clock(button_block *buttons, edison_button *sdl_buttons[BUTTON_NUMBER])
{
	bool btnStates[BUTTON_NUMBER];

	if(buttons)
	{
		if((buttons -> bus -> req) && (buttons -> bus -> address == buttons -> address) && (!buttons -> bus -> ack))
		{
			buttons -> bus -> ack = M_HIGH;

			for(int i = 0; i < BUTTON_NUMBER; i++)
			{
				btnStates[i] = edison_button_get_state(sdl_buttons[i]);
			}

			buttons -> bus -> data = boolToDec(btnStates);
		}
		else if(buttons -> bus -> ack && ((buttons -> bus -> address == buttons -> address)))
		{
			buttons -> bus -> ack = M_LOW;	
		}
	}
	return;
}

/*
 * Gets the Buttons block's bus
 *
 *
 *
 */

m_bus button_block_get_bus(button_block *buttons)
{
	m_bus bus = { 0 };
	if(!buttons)
	{
		return bus;
	}
	return *(buttons -> bus);
}

/*
 * boolToBin
 *
 * This functions transforms an array of booleans
 * in a binary integer
 *
 */

int boolToDec(bool *states)
{
	int number;

	for(int i = 0; i < (sizeof(states) / sizeof(states[0])); i++)
	{
		if(states[i])
		{
			number += pow(2, i);
		}
	}
	return number;
}

