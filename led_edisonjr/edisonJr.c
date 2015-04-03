/*
 *
 * EdisonJr
 *
 * Code for the Edison Jr!
 *
 * This is a virtual microprocessor experiment board!
 *
 */

// Headers

#include "/usr/local/include/SDL2/SDL.h"
#include "miniat/miniat.h"
#include "led_block.h"
#include "button_block.h"
#include "sevseg_display.h"
#include "dip_switch.h"

#include "SDL/edison_led_matrix.h"
#include "SDL/edison_led.h"
#include "SDL/edison_sdl.h"
#include "SDL/edison_button.h"
#include "SDL/edison_dipswitch.h"

// Memory addresses

#define LED_ADDRESS         0x4000
#define SEVSEG_ADDRESS      0x4010
#define BUTTONS_ADDRESS     0x4020
#define DIPSWITCH_ADDRESS   0x4030

// Main

int main(int argc, char *argv[])
{   
    /* 
     * Creating the peripherals
     *
     */

    miniat *iMiniAT = miniat_file_new(argv[1]);
    edison_board *board = edison_create_board(1200, 800);
    edison_led_matrix *matrix = edison_create_led_matrix(50, 550, 32, 16, 5, 0, 0, 255);
    edison_dipswitch *edison_switches = edison_create_dipswitch(550, 450, 40, 20);
    edison_button *buttons[8];

    led_block *ledBlock = led_block_new(LED_ADDRESS);
    button_block *btnBlock = button_block_new(BUTTONS_ADDRESS);
    sevseg_display *sevsegDisplay = sevseg_display_new(SEVSEG_ADDRESS);
    dip_switch *switches = dip_switch_new(DIPSWITCH_ADDRESS);

    /* 
     * Adding peripherals to the board and connecting them to the bus
     *
     */

    for(int i = 7; i >= 0; i--)
    {
        buttons[i] = edison_create_button(795 - (i * 35), 400, 20, 20);
        edison_add_button(board, buttons[i]);
    }

    edison_add_led_matrix(board, matrix);
    edison_add_dipswitch(board, edison_switches);

    led_block_bus_connector_set(ledBlock, miniat_conector_bus_get(iMiniAT));
    button_block_bus_connector_set(btnBlock, miniat_conector_bus_get(iMiniAT));
    sevseg_display_bus_connector_set(sevsegDisplay, miniat_conector_bus_get(iMiniAT));
    dip_switch_bus_connector_set(switches, miniat_conector_bus_get(iMiniAT));

    // This is the main loop. This is what keeps everything clocking (updating)
    // Also reads SDL events

    while(edison_poll_events(board))
    {
        // Clocks

        miniat_clock(iMiniAT);
        led_block_clock(ledBlock, matrix);
        button_block_clock(btnBlock, buttons);
        sevseg_display_clock(sevsegDisplay);
        dip_switch_clock(switches);
        edison_render(board);
    }
      
    // Memory cleaning

    edison_destroy_board(board);
    sevseg_display_free(sevsegDisplay);
    led_block_free(ledBlock);
    button_block_free(btnBlock);
    dip_switch_free(switches);
    miniat_free(iMiniAT);
    return 0;
}



