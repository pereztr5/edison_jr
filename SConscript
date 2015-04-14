Import('*')
import os

SDL2_CFLAGS = str.split(os.popen('sdl2-config --cflags').read())
SDL2_LIBS = str.split(os.popen('sdl2-config --libs').read())

INC = [ '#/vm/inc' ]

LIBS = [ 'libminiat' ]

EDISON_CFLAGS = []
EDISON_LIBPATH = str.split(env[ 'LIBPATH' ])

for flag in SDL2_CFLAGS:
    if flag.startswith("-I"):
        INC.append(flag[2:])
    else:
        EDISON_CFLAGS.append(flag)

for flag in SDL2_LIBS:
    if flag.startswith("-L"):
        EDISON_LIBPATH.append(flag[2:])
    else:
        LIBS.append(flag[2:])

buildProgram("miniat_edisonJr", ["edisonJr.c", "led_block.c", "sevseg_display.c", "button_block.c", "dip_switch.c", "lcd_display.c", "SDL/edison_lcd_display.c","SDL/edison_led.c", "SDL/edison_sdl.c", "SDL/edison_seven_segment.c", "SDL/edison_button.c", "SDL/edison_led_matrix.c", "SDL/edison_dipswitch.c"], CPPPATH=INC, LIBS=LIBS, CFLAGS=EDISON_CFLAGS, LIBPATH=EDISON_LIBPATH)
buildMash('assembly.asm')
