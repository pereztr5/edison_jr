#ifndef _EDISON_UTIL_H_
#define _EDISON_UTIL_H_

#include "SDL2/SDL.h"
/**
 * typedef for ease of use
 */

typedef unsigned int uint;
typedef SDL_Point edision_pos;

typedef struct edison_texture
{
	SDL_Texture* texture;
	SDL_Rect* rect;
	char* name;
} edison_texture;

#define EDISON_LED_SIZE			15
#define EDISON_LED_MAX			8192
#define EDISON_LED_GRID_MAX		4096
#define EDISON_BUTTON_MAX		32
#define EDISON_SWITCH_MAX		32
#define EDISON_SEVEN_SEG_MAX	64
#define EDISON_TEXTURE_MAX		64
#endif
