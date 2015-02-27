#include "edison_button.h"

edison_button* edison_create_button(int pos_x, int pos_y, uint width, uint height)
{
	edison_button* button = malloc(sizeof(edison_button));
	edison_button_set_position(button, pos_x, pos_y);
	edison_button_set_size(button, width, height);
	edison_button_set_state(button, 0);

}
void edison_button_set_position(edison_button* button, int pos_x, int pos_y)
{
	button->hitbox.x = pos_x;
	button->hitbox.y = pos_y;
}

void edison_button_set_size(edison_button* button, uint width, uint height)
{
	button->hitbox.w = width;
	button->hitbox.h = height;
}

void edison_button_set_state(edison_button* button, bool pressed)
{
	button->pressed = pressed;
}

bool edison_button_get_state(edison_button* button)
{
	return button->pressed;
}
