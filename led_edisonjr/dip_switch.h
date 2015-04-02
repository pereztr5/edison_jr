/*
 * Header file for the DIP Switch peripheral
 *
 *
 */

#ifndef _DIP_SWITCH_H_
#define _DIP_SWITCH_H_

#include "miniat/miniat.h"
//#include "SDL/edison_button.h"

typedef struct dip_switch dip_switch;

/*
 * Creates a new DIP Switch peripheral, setting it's address
 * to "address" for the miniAT
 *
 *
 *
 */

extern dip_switch *dip_switch_new(m_uword address);

/*
 * Free's the memory address for the DIP Switch passed
 * as argument
 *
 *
 *
 */

extern void dip_switch_free(dip_switch *switches);

/*
 * Clock function
 *
 * This will update the current value for the DIP Switch
 *
 *
 */

extern void dip_switch_clock(dip_switch *switches);

/*
 * Tries to connect the DIP Switch with the bus
 *
 *
 *
 *
 */

extern void dip_switch_bus_connector_set(dip_switch *switches, m_bus *bus);

/*
 * Sets the DIP Switch bus
 *
 *
 *
 *
 */

extern m_bus dip_switch_get_bus(dip_switch *switches);


#endif 