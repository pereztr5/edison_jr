/*
# C file for the LED peripheral
#
# This peripheral actually creates a group of LEDs
# instead of a single one.
#
# The bus has 32 bit size. We can decide how many
# we are going to assign to the bus, when creating
# an instance of this peripheral.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <miniat/miniat.h>
#include "led_block.h"

struct led_block
{
	int connected;
	m_uword address;
	m_bus *bus;
};

/*
#Function for creating a new LED block
#
#Allocates the memory space for the peripheral,
#
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
#Connects the LED block to the bus
#
#
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
#Free's the LED block
#
#The command free simply does the opposite of memory allocation (free's memory location)
#
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
#Updates the current state of the LED block
#
#This is where is must update the graphics
#
#If display is set (peripheral was created), then
#set the data that's being passed through the bus
#to generate the correct graphics.
#
*/

void led_block_clock(led_block *led)
{
	if(led)
	{
		if(led -> bus -> address == led -> address)
		{
			//edison_led_set_state(led, led -> bus -> data);
		}
	}

	return;
}

/*
#Sets the LED block's bus
#
#
#
*/

void led_block_set_bus(led_block *led, m_bus bus)
{
	if(led)
	{
		memcpy(led -> bus, &bus, sizeof(bus));
	}
	return;
}
