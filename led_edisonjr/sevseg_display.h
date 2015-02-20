/*
# Header file for the 7 segment display peripheral
#
#
*/

#ifndef _SEVSEG_DISPLAY_H_
#define _SEVSEG_DISPLAY_H_

#include "miniat/miniat.h"

typedef struct sevseg_display sevseg_display;

/*
#Creates a new 7 segment display peripheral, setting it's address
#to "address" for the miniAT
#
#
#
*/

extern sevseg_display *sevseg_display_new(m_uword address);

/*
#Free's the memory address for the 7 segment display passed
#as argument
#
#
#
*/

extern void sevseg_display_free(sevseg_display *display);

/*
#Clock function
#
#This will update the current value for the 7 segment display pins
#
#
*/

extern void sevseg_display_clock(sevseg_display *display);

/*
#Tries to connect the 7 segment display with the bus
#
#
#
#
*/

extern void sevseg_display_bus_connector_set(sevseg_display *display, m_bus *bus);

/*
# Sets the seven segment display bus
#
#
#
#
*/

extern void sevseg_display_set_bus(sevseg_display *display, m_bus bus);

#endif 