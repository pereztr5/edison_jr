#include "edison_seven_segment.h"

/*
struct edison_sevenseg
{
	uint id;
	struct SDL_Rect segs[8];
	int status[8];
};
*/

edison_sevenseg* edison_create_sevenseg(int pos_x, int pos_y, int width, int height, int offset_x, int offset_y, int dot_width)
{
	edison_sevenseg* sevenseg = malloc(sizeof(edison_sevenseg));
	//creation of segment display struct
	//segment display id - default to 0
	sevenseg->id = 0;
	//creation of rects, please refer to segment display design artifact for more information
	//first segment rect
	sevenseg->segs[0].x = pos_x+height+offset_x;
	sevenseg->segs[0].y = pos_y;
	sevenseg->segs[0].w = width;
	sevenseg->segs[0].h = height;
	//second segment rect
	sevenseg->segs[1].x = pos_x+height+offset_x*2+width;
	sevenseg->segs[1].y = pos_y+height+offset_y;
	sevenseg->segs[1].w = height;
	sevenseg->segs[1].h = width;
	//third segment rect 
	sevenseg->segs[2].x = pos_x+height+offset_x*2+width;
	sevenseg->segs[2].y = pos_y+height*2+offset_y*3+width;
	sevenseg->segs[2].w = height;
	sevenseg->segs[2].h = width;
	//fourth segment rect
	sevenseg->segs[3].x = pos_x+height+offset_x;
	sevenseg->segs[3].y = pos_y+height*2+offset_y*4+width*2;
	sevenseg->segs[3].w = width;
	sevenseg->segs[3].h = height;
	//fifth segment rect
	sevenseg->segs[4].x = pos_x;
	sevenseg->segs[4].y = pos_y+height*2+offset_y*3+width;
	sevenseg->segs[4].w = height;
	sevenseg->segs[4].h = width;
	//sixth segment rect
	sevenseg->segs[5].x = pos_x;
	sevenseg->segs[5].y = pos_y+height+offset_y;
	sevenseg->segs[5].w = height; 
	sevenseg->segs[5].h = width;
	//seventh segment rect
	sevenseg->segs[6].x = pos_x+height+offset_x;
	sevenseg->segs[6].y = pos_y+height+offset_y*2+width;
	sevenseg->segs[6].w = width;
	sevenseg->segs[6].h = height;
	//dot segment rect
	sevenseg->segs[7].x = pos_x+height*2+offset_x*3+width;
	sevenseg->segs[7].y = pos_y+height*2+offset_y*4+width*2;
	sevenseg->segs[7].w = dot_width;
	sevenseg->segs[7].h = height;
	//setting of default segment status' to 0 (off)
	sevenseg->status[0] = 0;
	sevenseg->status[1] = 0;
	sevenseg->status[2] = 0;
	sevenseg->status[3] = 0;
	sevenseg->status[4] = 0;
	sevenseg->status[5] = 0;
	sevenseg->status[6] = 0;
	sevenseg->status[7] = 0;
	//returns the pointer to the created structure
	return sevenseg;
}

void edison_sevenseg_set_state(edison_sevenseg* sevenseg, int state[8])
{
	int i;
	for(i=0;i<8;i++)
	{
		sevenseg->status[i]=state[i];
	}
}
