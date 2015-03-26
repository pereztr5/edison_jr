/*
 * Header file for the Button Block peripheral
 *
 *
 */

#ifndef _BUTTON_BLOCK_H_
#define _BUTTON_BLOCK_H_

#include "miniat/miniat.h"

typedef struct button_block button_block;

/*
 * Creates a new Button Block peripheral, setting it's address
 * to "address" for the miniAT
 *
 *
 *
 */

extern button_block *button_block_new(m_uword address);

/*
 * Free's the memory address for the Button Block passed
 * as argument
 *
 *
 *
 */

extern void button_block_free(button_block *buttons);

/*
 * Clock function
 *
 * This will update the current value for the Button Block
 *
 *
 */

extern void button_block_clock(button_block *buttons);

/*
 * Tries to connect the Button Block with the bus
 *
 *
 *
 *
 */

extern void button_block_bus_connector_set(button_block *buttons, m_bus *bus);

/*
 * Sets the Button block's bus
 *
 *
 *
 *
 */

extern m_bus button_block_get_bus(button_block *buttons);

#endif 