/*
* C file for the 7 segment display peripheral
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <miniat/miniat.h>
#include "sevseg_display.h"
#include "SDL/edison_seven_segment.h"


struct sevseg_display
{
	int connected;
	m_uword address;
	m_bus *bus;
};

/*
*Function for creating a new 7 segment display
*
*Allocates the memory space for the peripheral,
*
*/

sevseg_display *sevseg_display_new(m_uword address)
{

	sevseg_display *display = (sevseg_display *)malloc(sizeof(sevseg_display));
	
	if(display)
	{
		display -> bus = (m_bus *)malloc(sizeof(m_bus));
		
		if(!display -> bus)
		{
			free(display);
			display = NULL;
		}
		else
		{
			display -> address = address;
			display -> connected = 0;
		}
	}
	return display;
}

/*
*Connects the 7 segment display peripheral to the bus
*
*
*/

void sevseg_display_bus_connector_set(sevseg_display *display, m_bus *bus)
{

	if(display && bus)
	{
		
		if(!display -> connected)
		{
			free(display -> bus);
		}
		
		display -> bus = bus;
		display -> connected = 1;
	}
	return;
}

/*
*Free's the 7 segment display
*
*The command free simply does the opposite of memory allocation (free's memory location)
*
*/

void sevseg_display_free(sevseg_display *display)
{
	if(display)
	{
		if(!display -> connected)
		{
			free(display -> bus);
		}
		free(display);
	}
	return;
}

/*
*Updates the current state of the 7 segment display
*
*This is where is must update the graphics
*
*If display is set (peripheral was created), then
*set the data that's being passed through the bus
*to generate the correct graphics.
*
*/

void sevseg_display_clock(edison_sevenseg *sevseg ,sevseg_display *display)
{
    int *state = malloc(sizeof(int)*8);
    int i;

	if(display)
	{
		if((display -> bus -> req) && (display -> bus -> address == display -> address) && (!display -> bus -> ack))
		{
            display -> bus -> ack = M_HIGH;

            // Convert Decimal Number to binary and store into an array of size 8
            state = decimal_to_binary(display -> bus -> data);

            edison_sevenseg_set_state(sevseg, state);
		}
        else if(display -> bus -> ack && ((display -> bus -> address == display -> address)))
        {
            display -> bus -> ack = M_LOW;
        }
	}
	return;
}

/*
* Sets the seven segment display bus
*
*/

void sevseg_display_set_bus(sevseg_display *display, m_bus bus)
{
	if(display)
	{
		memcpy(display -> bus, &bus, sizeof(bus));
	}
	return;
}

/*
* Function to convert a decimal value to binary.
* This returns an array
*
*/

int *decimal_to_binary ( int segment_data )
{

    int *binary = malloc(sizeof(int)*8);
    int *state = malloc(sizeof(int)*8);
    int i;

    for( i=0; i <8; i++) {
        binary[i] = segment_data % 2;
        segment_data = segment_data/2;
    }

    return binary;
}
