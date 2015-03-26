#include "edison_dipswitch.h"

struct edison_dipswitch
{
	uint id;
	struct SDL_Rect rect;
	int status;
};

edison_dipswitch* edison_create_dipswitch(int pos_x, int pos_y, int width, int height)
{
	//dipswitch creation
	edison_dipswitch* dipswitch = malloc(sizeof(edison_dipswitch));

	//gives the dipswitch a default id of 0
	dipswitch->id = 0;
	//creates the dipswitch rectangle
	dipswitch->rect.x = pos_x;
	dipswitch->rect.y = pos_y;
	dipswitch->rect.w = width;
	dipswitch->rect.h = height;
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