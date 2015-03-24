/*
#
# EdisonJr
#
# Code for the Edison Jr!
#
# This is a virtual microprocessor experiment board!
# 
*/

// Libraries

#include <stdio.h>
#include <stdlib.h>

// Headers

#include "/usr/local/include/SDL2/SDL.h"
#include "miniat/miniat.h"
#include "led_block.h"
#include "button_block.h"
#include "sevseg_display.h"

// Memory addresses

#define LED_ADDRESS         0x4000
#define SEVSEG_ADDRESS      0x4010
#define BUTTONS_ADDRESS     0x4020

/*
#
# MAIN 
#
# 
# 
*/

int main(int argc, char *argv[])
{
    /*
    Creating instances of peripherals and miniat.

    This is simply allocating memory using the defined addresses on the define
    statements
    */
      
    miniat *iMiniAT = miniat_file_new(argv[1]);

    led_block *ledBlock = led_block_new(LED_ADDRESS);
    button_block *btnBlock = button_block_new(BUTTONS_ADDRESS);
    sevseg_display *sevsegDisplay = sevseg_display_new(SEVSEG_ADDRESS);

    // Connecting peripherals to the miniat's bus

    led_block_bus_connector_set(ledBlock, miniat_conector_bus_get(iMiniAT));
    button_block_bus_connector_set(btnBlock, miniat_conector_bus_get(iMiniAT));
    sevseg_display_bus_connector_set(sevsegDisplay, miniat_conector_bus_get(iMiniAT));

    // This is the main loop. This is what keeps everything clocking (updating)

    while(1)
    {
        //m_wyde portA, portB;

        // Clocks

        miniat_clock(iMiniAT);
        button_block_clock(btnBlock);
        sevseg_display_clock(sevsegDisplay);
        led_block_clock(ledBlock);

            
    }
      
    // Memory cleaning

    sevseg_display_free(sevsegDisplay);
    led_block_free(ledBlock);
    button_block_free(btnBlock);
    miniat_free(iMiniAT);
    return 0; 
}