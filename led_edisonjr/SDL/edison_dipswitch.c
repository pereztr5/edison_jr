#include "edison_dipswitch.h"

struct edison_dipswitch
{
	uint id;
	struct SDL_Rect rects[2];
	int status[4];
};

edison_dipswitch* edison_create_dipswitch(int pos_x, int pos_y, int width, int height)
{
	//dipswitch creation
	edison_dipswitch* dipswitch = malloc(sizeof(edison_dipswitch));

	//gives the dipswitch a default id of 0
	dipswitch->id = 0;
	//creates the dipswitch rectangles
	dipswitch->rects[0].x = pos_x;
	dipswitch->rects[0].y = pos_y;
	dipswitch->rects[0].w = width;
	dipswitch->rects[0].h = height/2;
	dipswitch->rects[1].x = pos_x;
	dipswitch->rects[1].y = pos_y + height/2;
	dipswitch->rects[1].w = width;
	dipswitch->rects[1].h = height/2;

	//sets defualt dipswitch state to 0
	for(int i = 0; sizeof(dipswitch -> status) / sizeof(int); i++)
		dipswitch -> status[i] = 0;

	//returns pointer to dipswitch
	return dipswitch;
}

void edison_dipswitch_set_state(edison_dipswitch* dipswitch, int* state)
{
	//sets dipswitch state to sent state.
	for(int i = 0; i < sizeof(state) / sizeof(state[0]); i++)
		dipswitch -> status[i] = state[i];
}

int* edison_dipswitch_get_state(edison_dipswitch* dipswitch)
{
	return dipswitch -> status;
}