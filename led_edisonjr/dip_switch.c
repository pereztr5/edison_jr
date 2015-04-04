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
#include "button_block.h"

#define SWITCHES_NUMBER 4

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

void dip_switch_clock(dip_switch *switches, edison_dipswitch *edison_switches)
{
	bool switch_states[SWITCHES_NUMBER];
	int *temp_states;
	int j = SWITCHES_NUMBER - 1;

	temp_states = malloc(sizeof(int) * SWITCHES_NUMBER);

	if(switches)
	{
		if((switches -> bus -> req) && (switches -> bus -> address == switches -> address) && (!switches -> bus -> ack))
		{
			switches -> bus -> ack = M_HIGH;

			temp_states = edison_dipswitch_get_state(edison_switches);

			for(int i = 0; i < SWITCHES_NUMBER; i++)
			{
				if(temp_states[j] == 1)
				{
					switch_states[i] = true;
				}
				else
				{
					switch_states[i] = false;
				}
				j--;
			}
			
			switches -> bus -> data = boolToDecimal(switch_states);
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

/*
 * boolToBin
 *
 * This functions transforms an array of booleans
 * in a binary integer
 *
 */

int boolToDecimal(bool *states)
{
	int number;

	for(int i = 0; i < SWITCHES_NUMBER; i++)
	{
		if(states[i])
		{
			number += pow(2, i);
		}
	}
	return number;
}

