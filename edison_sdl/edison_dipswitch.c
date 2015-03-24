#include "edison_dipswitch.h"

struct edison_dipswitch
{
	uint id;
	struct SDL_Rect rects[2];
	int status;
};

edison_dipswitch* edison_create_dipswitch(int pos_x, int pos_y, int width, int height)
{
	//dipswitch creation
	edison_dipswitch* dipswitch = malloc(sizeof(edison_dipswitch));

	//gives the dipswitch a default id of 0
	dipswitch->id = 0;
	//creates the dipswitch rectangles
	dipswitch->rect[0].x = pos_x;
	dipswitch->rect[0].y = pos_y;
	dipswitch->rect[0].w = width;
	dipswitch->rect[0].h = height/2;
	dipswitch->rect[1].x = pos_x;
	dipswitch->rect[1].y = pos_y + height/2;
	dipswitch->rect[1].w = width;
	dipswitch->rect[1].h = height/2;
	//sets defualt dipswitch state to 0
	dipswitch->status = 0;

	//returns pointer to dipswitch
	return dipswitch;
}

void edison_dipswitch_set_state(edison_dipswitch* dipswitch, int state)
{
	//sets dipswitch state to sent state.
	dipswitch->status = state;
}