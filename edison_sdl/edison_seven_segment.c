#include "edison_seven_segment.h"

edison_sevenseg* edison_create_sevenseg(int pos_x, int pos_y, int width, int height)
{
	edison_sevenseg* sevenseg = malloc(sizeof(edison_sevenseg));
	*sevenseg = {NULL,
				 {{pos_x+height, pos_y, width, height},
				  {pos_x+width+height, pos_y+height, height, width},
				  {pos_x+width+height, pos_y+2*height+width, height, width},
				  {pos_x+height, pos_y+2*width+2*height, width, height},
				  {pos_x, pos_y+2*height+width, height, width},
				  {pos_x, pos_y+height, height, width},
				  {pos_x+height, pos_y+height+width, width, height}
				  {pos_x+2*height+width, pos_y+2*height+2*width, width/2, height}
				 },
				 {0,0,0,0,0,0,0,0}
				};
	return sevenseg;
}

void edison_sevenseg_set_state(edison_sevenseg* sevenseg, int state[8])
{
	int i;
	for(i=0;i<8;i++)
	{
		*sevenseg.status[i]=state[i];
	}
}