#ifndef _EDISON_UTIL_H_
#define _EDISON_UTIL_H_

/**
 * typedef for ease of use
 */

typedef unsigned int uint;
typedef SDL_Point edision_pos;

typedef struct edison_texture
{
	SDL_Texture* texture;
	SDL_Rect rect;
} edison_texture;

#endif