/*
EdisonJr

gcc -I "../../../../out/vm/inc/miniat/" -c EdisonJr.c 
gcc -o EdisonJr -L "../../../../out/lib/" EdisonJr.o -lminiat
mash assembly.asm 
*/

#include <stdio.h>
#include <stdlib.h>

#include "miniat/miniat.h"
#include "led_block.h"
#include "sevseg_display.h"

int main(int argc, char *argv[])
{
    m_bus *bus_state;
      
    miniat *iMiniAT = miniat_file_new(argv[1]);

    bus_state = miniat_conector_bus_get(iMiniAT);
    
    led_block *ledBlock = led_block_new(0x4000);
    sevseg_display *sevsegDisplay = sevseg_display_new(0x400A);

    led_block_bus_connector_set(ledBlock, bus_state);
    sevseg_display_bus_connector_set(sevsegDisplay, bus_state);

    
    
    
    
      printf("Welcome to Edison Jr.!\n");

      while(1)
      {
            m_wyde portA;
            miniat_clock(iMiniAT);
            sevseg_display_clock(sevsegDisplay);
            led_block_clock(ledBlock);

            //portA = miniat_pins_get_gpio_port(iMiniAT, m_gpio_id_A);
            

            printf("%d%d%d%d%d\n", portA.bit4, portA.bit3, portA.bit2, portA.bit1, portA.bit0);
      }
      

      sevseg_display_free(sevsegDisplay);
      led_block_free(ledBlock);
      miniat_free(iMiniAT);
      return 0; 
}