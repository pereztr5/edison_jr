/*
 * C file for the Button Block peripheral
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Updates the current state of the Button block
 *
 *
 *
 */

void button_block_clock(button_block *buttons)
{
	if(buttons)
	{
		if((buttons -> bus -> address == buttons -> address) && (!buttons -> bus -> ack))
		{
			buttons -> bus -> ack = M_HIGH;

			/*
			 *
			 * THIS IS WHERE THE EVENT HANDLER IS PUT!
			 *
			 *
			 * EVERYTIME THE BUTTON CLOCKS, IT READS THE STATES OF THE BUTTONS
			 *
			 * FUNCTION SHOULD LOOK SOMETHING LIKE THIS
			 *
			 * buttons -> bus -> data = event_handler_function();
			 *
			 * Using this idea, the event handler function should read which button was pressed, and return the
			 * current state of all the buttons as a whole. Then that result is sent to the bus, and the assembly
			 * programer can read it through the assigned memory address.
			 *
			 */
			

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


