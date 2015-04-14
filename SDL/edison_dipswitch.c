#include "edison_dipswitch.h"
#include <stdio.h>

edison_dipswitch* edison_create_dipswitch(int pos_x, int pos_y, int width, int height)
{
	//dipswitch creation
	edison_dipswitch* dipswitch = malloc(sizeof(edison_dipswitch));

	//gives the dipswitch a default id of 0
	dipswitch->id = 0;

	//creates the dipswitch rectangles
	//please see design document for more info
	for(int i = 0; i<8;i=i+2){
		dipswitch->rects[i].x = pos_x+(i*(width/7));
		dipswitch->rects[i].y = pos_y;
		dipswitch->rects[i].w = width/7;
		dipswitch->rects[i].h = height/2;
		dipswitch->rects[i+1].x = pos_x+(i*(width/7));
		dipswitch->rects[i+1].y = pos_y + height/2;
		dipswitch->rects[i+1].w = width/7;
		dipswitch->rects[i+1].h = height/2;
	}

	
	//sets defualt dipswitch state to 0
	for(int i = 0; i < (sizeof(dipswitch -> status) / sizeof(dipswitch -> status[0])); i++)
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
