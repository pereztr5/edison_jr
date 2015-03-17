/*
# Header file for the LED peripheral
#
#
*/

#ifndef _LED_BLOCK_H_
#define _LED_BLOCK_H_

#include "miniat/miniat.h"

typedef struct led_block led_block;

/*
# Creates a new LED peripheral, setting it's address
# to "address" for the miniAT
#
#
#
*/

extern led_block *led_block_new(m_uword address);

/*
# Free's the memory address for the LED passed
# as argument
#
#
#
*/

extern void led_block_free(led_block *led);

/*
# Clock function
#
# This will update the current value for the LED pin
#
#
*/

extern void led_block_clock(led_block *led);

/*
# Tries to connect the LED with the bus
#
#
#
#
*/

extern void led_block_bus_connector_set(led_block *led, m_bus *bus);

/*
# Sets the LED block's bus
#
#
#
#
*/

extern void led_block_set_bus(led_block *led, m_bus bus);

#endif 