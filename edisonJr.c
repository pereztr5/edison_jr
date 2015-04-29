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

#include "SDL2/SDL.h"
#include "miniat/miniat.h"
#include "led_block.h"
#include "button_block.h"
#include "sevseg_display.h"
#include "dip_switch.h"
#include "lcd_display.h"

#include "SDL/edison_led_matrix.h"
#include "SDL/edison_led.h"
#include "SDL/edison_sdl.h"
#include "SDL/edison_button.h"
#include "SDL/edison_dipswitch.h"
#include "SDL/edison_lcd_display.h"
#include "SDL/edison_potentiometer.h"

// Memory addresses

#define LED_ADDRESS         0x4000
#define SEVSEG_ADDRESS_1      0x4010
#define SEVSEG_ADDRESS_2      0x4011
#define SEVSEG_ADDRESS_3      0x4012
#define SEVSEG_ADDRESS_4      0x4013
#define BUTTONS_ADDRESS     0x4020
#define DIPSWITCH_ADDRESS   0x4030
#define LCD_DISPLAY_ADDRESS 0x4040

// Important Numbers

#define BUTTON_NUMBER 8

// Main

int main(int argc, char *argv[])
{
    /* 
     * Variable dictionary
     *
     *      delay_ratio : the delay ratio caused by the potentiometer to slow down simulation
     *      cycles      : number of cycles executed. Used to produce the delay
     */

    int delay_ratio = 1;
    int cycles = 0;

    /* 
     * Creating the peripherals
     *
     */

    miniat *iMiniAT = miniat_file_new(argv[1]);
    edison_board *board = edison_create_board(1200, 800);
    edison_led_matrix *matrix = edison_create_led_matrix(50, 550, 32, 16, 5, 0, 0, 255);
    edison_dipswitch *edison_switches = edison_create_dipswitch(550, 450, 80, 45);
    edison_lcd_display *edison_lcd = edison_create_lcd_display();
    edison_potentiometer *edison_pot = edison_create_potentiometer();
    edison_button *buttons[BUTTON_NUMBER];
    edison_sevenseg *sevseg1 = edison_create_sevenseg(175, 400, 35, 6, 2, 2, 6);
    edison_sevenseg *sevseg2 = edison_create_sevenseg(250, 400, 35, 6, 2, 2, 6);
    edison_sevenseg *sevseg3 = edison_create_sevenseg(325, 400, 35, 6, 2, 2, 6);
    edison_sevenseg *sevseg4 = edison_create_sevenseg(400, 400, 35, 6, 2, 2, 6);

    led_block *ledBlock = led_block_new(LED_ADDRESS);
    button_block *btnBlock = button_block_new(BUTTONS_ADDRESS);
    sevseg_display *sevsegDisplay_1 = sevseg_display_new(SEVSEG_ADDRESS_1);
    sevseg_display *sevsegDisplay_2 = sevseg_display_new(SEVSEG_ADDRESS_2);
    sevseg_display *sevsegDisplay_3 = sevseg_display_new(SEVSEG_ADDRESS_3);
    sevseg_display *sevsegDisplay_4 = sevseg_display_new(SEVSEG_ADDRESS_4);
    dip_switch *switches = dip_switch_new(DIPSWITCH_ADDRESS);
    lcd_display *lcd = lcd_display_new(LCD_DISPLAY_ADDRESS);

    /* 
     * Adding peripherals to the board and connecting them to the bus
     *
     */

    for(int i = BUTTON_NUMBER - 1; i >= 0; i--)
    {
        buttons[i] = edison_create_button(795 - (i * 35), 400, 20, 20);
        edison_add_button(board, buttons[i]);
    }

    edison_add_led_matrix(board, matrix);
    edison_add_dipswitch(board, edison_switches);
    edison_add_lcd_display(board, edison_lcd);
    edison_add_potentiometer(board, edison_pot);
    edison_add_sevenseg(board, sevseg1);
    edison_add_sevenseg(board, sevseg2);
    edison_add_sevenseg(board, sevseg3);
    edison_add_sevenseg(board, sevseg4);

    led_block_bus_connector_set(ledBlock, miniat_conector_bus_get(iMiniAT));
    button_block_bus_connector_set(btnBlock, miniat_conector_bus_get(iMiniAT));
    sevseg_display_bus_connector_set(sevsegDisplay_1, miniat_conector_bus_get(iMiniAT));
    sevseg_display_bus_connector_set(sevsegDisplay_2, miniat_conector_bus_get(iMiniAT));
    sevseg_display_bus_connector_set(sevsegDisplay_3, miniat_conector_bus_get(iMiniAT));
    sevseg_display_bus_connector_set(sevsegDisplay_4, miniat_conector_bus_get(iMiniAT));
    dip_switch_bus_connector_set(switches, miniat_conector_bus_get(iMiniAT));
    lcd_display_bus_connector_set(lcd, miniat_conector_bus_get(iMiniAT));

    // This is the main loop. This is what keeps everything clocking (updating)
    // Also reads SDL events

    while(edison_poll_events(board))
    {
        // This is just to prevent that cycles gets bigger than int capacity

        if(cycles > 100000 * delay_ratio)
        {
            cycles = 0;
        }

        /* 
         * This if statement is what generates the potentiometer effect
         *
         * If potentiometer is not in standard position, everything will only clock
         * a ratio of the times it would normally.
         *
         */

        if(cycles % delay_ratio == 0)
        {
            // Clocks

            miniat_clock(iMiniAT);
            led_block_clock(ledBlock, matrix);
            button_block_clock(btnBlock, buttons);
            sevseg_display_clock(sevseg1,sevsegDisplay_1);
            sevseg_display_clock(sevseg2,sevsegDisplay_2);
            sevseg_display_clock(sevseg3,sevsegDisplay_3);
            sevseg_display_clock(sevseg4,sevsegDisplay_4);
            dip_switch_clock(switches, edison_switches);
            lcd_display_clock(lcd, edison_lcd);    
        }
        
        delay_ratio = edison_potentiometer_get_pos(edison_pot);
        edison_render(board);
        cycles++;
    }
      
    // Memory cleaning

    edison_destroy_board(board);
    sevseg_display_free(sevsegDisplay_1);
    sevseg_display_free(sevsegDisplay_2);
    sevseg_display_free(sevsegDisplay_3);
    sevseg_display_free(sevsegDisplay_4);
    led_block_free(ledBlock);
    button_block_free(btnBlock);
    dip_switch_free(switches);
    //lcd_display_free(lcd);
    miniat_free(iMiniAT);
    return 0;
}



