/*
 * C file for the DIP Switch peripheral
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <miniat/miniat.h>
#include "dip_switch.h"

struct dip_switch
{
	int connected;
	m_uword address;
	m_bus *bus;
};

/*
 * Function for creating a new DIP Switch
 *
 * Allocates the memory space for the peripheral,
 *
 */

dip_switch *dip_switch_new(m_uword address)
{

	dip_switch *switches = (dip_switch *)malloc(sizeof(dip_switch));
	
	if(switches)
	{
		switches -> bus = (m_bus *)malloc(sizeof(m_bus));
		
		if(!switches -> bus)
		{
			free(switches);
			switches = NULL;
		}
		else
		{
			switches -> address = address;
			switches -> connected = 0;
		}
	}
	return switches;
}

/*
 * Connects the DIP Switch to the bus
 *
 *
 */

void dip_switch_bus_connector_set(dip_switch *switches, m_bus *bus)
{

	if(switches && bus)
	{
		
		if(!switches -> connected)
		{
			free(switches -> bus);
		}
		
		switches -> bus = bus;
		switches -> connected = 1;
	}
	return;
}

/*
 * Free's the DIP Switch
 *
 * The command free simply does the opposite of memory allocation (free's memory location)
 *
 */

void dip_switch_free(dip_switch *switches)
{
	if(switches)
	{
		if(!switches -> connected)
		{
			free(switches -> bus);
		}
		free(switches);
	}
	return;
}

/*
 * Updates the current state of the DIP Switch
 *
 *
 *
 */

void dip_switch_clock(dip_switch *switches)
{

	if(switches)
	{
		if((switches -> bus -> req) && (switches -> bus -> address == switches -> address) && (!switches -> bus -> ack))
		{
			switches -> bus -> ack = M_HIGH;

			// SDL FUNCTIONS
		}
		else if(switches -> bus -> ack && ((switches -> bus -> address == switches -> address)))
		{
			switches -> bus -> ack = M_LOW;	
		}
	}
	return;
}

/*
 * Gets the switches DIP Switch bus
 *
 *
 *
 */

m_bus dip_switch_get_bus(dip_switch *switches)
{
	m_bus bus = { 0 };
	if(!switches)
	{
		return bus;
	}
	return *(switches -> bus);
}


