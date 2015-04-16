#include "edison_sdl.h"
#include <stdio.h>

#define LCD_IMAGE_PATH "images/display.bmp"

struct edison_board
{
	edison_led* led_list[EDISON_LED_MAX];
	uint led_count;
	edison_button* button_list[EDISON_BUTTON_MAX];
	uint button_count;
	edison_sevenseg* sevenseg_list[EDISON_SEVEN_SEG_MAX];
	uint sevenseg_count;
	edison_dipswitch* dipswitch_list[EDISON_SWITCH_MAX];
	uint dipswitch_count;
	edison_lcd_display *edison_lcd;
	SDL_Point board_size;
	SDL_Window* window;
	SDL_Surface* board_surface;
	SDL_Renderer* renderer;
	edison_texture* bg_texture;
};


/**
 * Creates a board
 */
edison_board* edison_create_board(uint size_x, uint size_y)
{
	edison_board* board = malloc(sizeof(edison_board));

	// Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL init error: %s\n", SDL_GetError());
		free(board);
		return NULL;
	}
	else
    {
    	// Init window
		board->window = SDL_CreateWindow("Edison Jr.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size_x, size_y, SDL_WINDOW_SHOWN);

		if(board->window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			free(board);
			return NULL;
		}
		else
		{
			board->renderer = SDL_CreateRenderer(board->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
			if(board->renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				free(board);
				return NULL;
			}
			else
			{

            }
            SDL_Point size = {size_x, size_y};
			board->board_size = size;
		}
	}

	board->led_count = 0;
	//board->switch_count = 0;

	return board;
}

/**
 * Destroys a board
 */
void edison_destroy_board(edison_board* board)
{
	// Cleanup
	SDL_FreeSurface(board->board_surface);
	SDL_DestroyRenderer(board->renderer);
	SDL_DestroyWindow(board->window);
	SDL_Quit();
	free(board);
}

/**
 * Adds an LED to the board
 */
void edison_add_led(edison_board* board, edison_led* led)
{
	if(board->led_count < EDISON_LED_MAX)
		board->led_list[board->led_count++] = led;
}


/**
 * Gets a given LED from the board
 */
edison_led* edison_get_led(edison_board* board, uint id)
{
	if(id < board->led_count)
	{
		return board->led_list[id];
	}

	return NULL;
}

/**
 * Renders all LEDs on a board
 */
void edison_render_leds(edison_board* board)
{
	uint i = 0;

	// Render all LEDs
	for(; i < board->led_count; i++)
	{
		edison_led* led = board->led_list[i];

		SDL_Color temp = led->color;
		
		if(!led->state)
		{
			temp.r *= .5;
			temp.g *= .5;
			temp.b *= .5;
		}

		SDL_Rect rect = {led->position.x, led->position.y, EDISON_LED_SIZE, EDISON_LED_SIZE};
		SDL_SetRenderDrawColor(board->renderer, temp.r,  temp.g, temp.b, 255);
		SDL_RenderFillRect(board->renderer, &rect);	
	}
}

void edison_add_button(edison_board* board, edison_button* button)
{
	if(board->button_count < EDISON_BUTTON_MAX)
	{
		board -> button_list[board->button_count++] = button;
	}

	return;
}

edison_button* edison_get_button(edison_board* board, uint id)
{
	if(id < board->button_count)
	{
		return board->button_list[id];
	}

	return NULL;
}
void edison_render_buttons(edison_board* board)
{
	// Render all buttons
	int i;

	for(i = 0; i < board->button_count; i++)
	{
		edison_button* button = board->button_list[i];
		SDL_Color temp = {255, 0, 0, 255};
		
		if(button->pressed)
		{

			temp.b = 255;
		}
		
		SDL_SetRenderDrawColor(board->renderer, temp.r, temp.g, temp.b, 255);
		SDL_RenderFillRect(board->renderer, &button->hitbox);
	}
}

void edison_add_led_matrix(edison_board* board, edison_led_matrix* mat)
{
	uint i = 0;
	for(; i < ((int)mat->led_count_x) * ((int)mat->led_count_y); i++)
	{
		edison_led* led = mat->led_grid[i];
		board->led_list[board->led_count++] = led;
	}
}

void edison_add_sevenseg(edison_board* board, edison_sevenseg* sevenseg)
{
	if(board->sevenseg_count < 20)
		board->sevenseg_list[board->sevenseg_count++] = sevenseg;
}
edison_sevenseg* edison_get_sevenseg(edison_board* board, uint id)
{
	if(id < board->sevenseg_count)
	{
		return board->sevenseg_list[id];
	}

	return NULL;
}
void edison_render_sevensegs(edison_board* board)
{
	uint i = 0;
	uint j = 0;
	for(; i < board->sevenseg_count; i++)
	{
		edison_sevenseg* sevenseg = board->sevenseg_list[i];
		for(j=0; j < 8; j++)
		{
			SDL_SetRenderDrawColor(board->renderer, 224 * sevenseg->status[j] + 31, 0, 0, 255);
			SDL_RenderFillRect(board->renderer, &sevenseg->segs[j]);
		}
	}
}

void edison_add_dipswitch(edison_board* board, edison_dipswitch* dipswitch)
{
	if(board->dipswitch_count < EDISON_SWITCH_MAX)
		board->dipswitch_list[board->dipswitch_count++] = dipswitch;
}

edison_dipswitch* edison_get_dipswitch(edison_board* board, uint id)
{
	if(id < board->dipswitch_count)
	{
		return board->dipswitch_list[id];
	}

	return NULL;
}

void edison_render_dipswitches(edison_board* board)
{
		uint i = 0;
		uint j = 0;
		uint color = 0;
		for(i = 0; i < board->dipswitch_count; i++)
		{
			edison_dipswitch* dipswitch = board->dipswitch_list[i];
			for(j=0; j < 8; j++)
			{
				if(j%2)
				{
					color = 67 + ((1 - dipswitch->status[j/2]) * 86);
				}
				else
				{
					color = 67 + (dipswitch->status[j/2] * 86);
				}
				SDL_SetRenderDrawColor(board->renderer, color, color, color, 255);
				SDL_RenderFillRect(board->renderer, &dipswitch->rects[j]);
			}
		}
}

void edison_add_lcd_display(edison_board *board, edison_lcd_display *lcd)
{
	board -> edison_lcd = lcd;
	return;
}

void edison_render_lcd_display(edison_board* board)
{
	SDL_Rect borders;
	SDL_Texture *temp_texture;
	SDL_Surface *temp_surface;
	char temp_char;
	bool nochar;
	int i, j;

	borders.x = 20;
	borders.y = 45;
	borders.w = 500;
	borders.h = 200;

	temp_surface = SDL_LoadBMP(LCD_IMAGE_PATH);

	if(temp_surface == NULL)
	{
		printf("%s\n", SDL_GetError());
	}
	else
	{
		temp_texture = SDL_CreateTextureFromSurface(board -> renderer, temp_surface);
		SDL_RenderCopy(board -> renderer, temp_texture, NULL, &borders);
	}

	borders.x = 34;
	borders.y = 62;
	borders.w = 16;
	borders.h = 26;

	for(i = 0; i < MAX_LINES; i++)
	{
		for(j = 0; j < MAX_CHARS; j++)
		{
			nochar = false;
			temp_char = board -> edison_lcd -> display_content[MAX_CHARS * i + j];

			switch(temp_char)
			{
				case 'a':
					temp_surface = SDL_LoadBMP("images/a.bmp");
					break;
				case 'b':
					temp_surface = SDL_LoadBMP("images/b.bmp");
					break;
				case 'c':
					temp_surface = SDL_LoadBMP("images/c.bmp");
					break;
				case 'd':
					temp_surface = SDL_LoadBMP("images/d.bmp");
					break;
				case 'e':
					temp_surface = SDL_LoadBMP("images/e.bmp");
					break;
				case 'f':
					temp_surface = SDL_LoadBMP("images/f.bmp");
					break;
				case 'g':
					temp_surface = SDL_LoadBMP("images/g.bmp");
					break;
				case 'h':
					temp_surface = SDL_LoadBMP("images/h.bmp");
					break;
				case 'i':
					temp_surface = SDL_LoadBMP("images/i.bmp");
					break;
				case 'j':
					temp_surface = SDL_LoadBMP("images/j.bmp");
					break;
				case 'k':
					temp_surface = SDL_LoadBMP("images/k.bmp");
					break;
				case 'l':
					temp_surface = SDL_LoadBMP("images/l.bmp");
					break;
				case 'm':
					temp_surface = SDL_LoadBMP("images/m.bmp");
					break;
				case 'n':
					temp_surface = SDL_LoadBMP("images/n.bmp");
					break;
				case 'o':
					temp_surface = SDL_LoadBMP("images/o.bmp");
					break;
				case 'p':
					temp_surface = SDL_LoadBMP("images/p.bmp");
					break;
				case 'q':
					temp_surface = SDL_LoadBMP("images/q.bmp");
					break;
				case 'r':
					temp_surface = SDL_LoadBMP("images/r.bmp");
					break;
				case 's':
					temp_surface = SDL_LoadBMP("images/s.bmp");
					break;
				case 't':
					temp_surface = SDL_LoadBMP("images/t.bmp");
					break;
				case 'u':
					temp_surface = SDL_LoadBMP("images/u.bmp");
					break;
				case 'v':
					temp_surface = SDL_LoadBMP("images/v.bmp");
					break;
				case 'w':
					temp_surface = SDL_LoadBMP("images/w.bmp");
					break;
				case 'x':
					temp_surface = SDL_LoadBMP("images/x.bmp");
					break;
				case 'y':
					temp_surface = SDL_LoadBMP("images/y.bmp");
					break;
				case 'z':
					temp_surface = SDL_LoadBMP("images/z.bmp");
					break;
				case '0':
					temp_surface = SDL_LoadBMP("images/0.bmp");
					break;
				case '1':
					temp_surface = SDL_LoadBMP("images/1.bmp");
					break;
				case '2':
					temp_surface = SDL_LoadBMP("images/2.bmp");
					break;
				case '3':
					temp_surface = SDL_LoadBMP("images/3.bmp");
					break;
				case '4':
					temp_surface = SDL_LoadBMP("images/4.bmp");
					break;
				case '5':
					temp_surface = SDL_LoadBMP("images/5.bmp");
					break;
				case '6':
					temp_surface = SDL_LoadBMP("images/6.bmp");
					break;
				case '7':
					temp_surface = SDL_LoadBMP("images/7.bmp");
					break;
				case '8':
					temp_surface = SDL_LoadBMP("images/8.bmp");
					break;
				case '9':
					temp_surface = SDL_LoadBMP("images/9.bmp");
					break;
				default:
					nochar = true;
					break;
			}
			
			if(!nochar)
			{
				if(temp_surface == NULL)
				{
					printf("%s\n", SDL_GetError());
				}
				else
				{
					temp_texture = SDL_CreateTextureFromSurface(board -> renderer, temp_surface);
					SDL_RenderCopy(board -> renderer, temp_texture, NULL, &borders);
				}
			}
			
			borders.x += 24;
		}
		borders.x = 34;
		borders.y += 35;
	}

	SDL_FreeSurface(temp_surface);
	SDL_DestroyTexture(temp_texture);
	return;
}

/**
 * Renders the given board
 */
void edison_render(edison_board* board)
{
	SDL_SetRenderDrawColor(board->renderer, 0, 50, 0, 0);
	SDL_RenderClear(board->renderer);
	edison_render_leds(board);
	edison_render_buttons(board);
	edison_render_sevensegs(board);
	edison_render_dipswitches(board);
	edison_render_lcd_display(board);
	SDL_RenderPresent(board->renderer);
}

bool edison_poll_events(edison_board* board)
{
	SDL_Event e;
	int *dipswstatarr; 
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

	dipswstatarr = malloc(sizeof(int) * 4);

	while(SDL_PollEvent(&e) != 0)
	{
		switch(e.type)
		{
			case SDL_QUIT:
				return false;
			break;
			case SDL_MOUSEBUTTONDOWN:

			i = 0;
			j = 0;
			SDL_GetMouseState(&x, &y);
			for(; i < board->button_count; i++)
			{
				// Check for button hit
				SDL_Rect hitbox = board->button_list[i]->hitbox;

				if(x > hitbox.x && x < (hitbox.x + hitbox.w) &&
					y > hitbox.y && y < (hitbox.y + hitbox.h))
				{
					//the button is pressed
					edison_button_set_state(board->button_list[i], 1);
				}
			}
			for(i = 0; i < board->dipswitch_count; i++)
			{
				dipswstatarr = edison_dipswitch_get_state(board->dipswitch_list[i]);
				// Check for dipswitch hit
				for(j = 0; j < 8; j=j+2){
					SDL_Rect hitbox = board->dipswitch_list[i]->rects[j];
					if(x > hitbox.x && x < (hitbox.x + hitbox.w) &&
						y > hitbox.y && y < (hitbox.y + (hitbox.h * 2)))
					{
						dipswstatarr[j/2] = 1 - dipswstatarr[j/2];
					}
				}
				edison_dipswitch_set_state(board->dipswitch_list[i], dipswstatarr);
			}
			break;

			case SDL_MOUSEBUTTONUP:

			i = 0;
			SDL_GetMouseState(&x, &y);
			for(; i < board->button_count; i++)
			{
				// Check for button hit
				SDL_Rect hitbox = board->button_list[i]->hitbox;

				if(x > hitbox.x && x < (hitbox.x + hitbox.w) &&
					y > hitbox.y && y < (hitbox.y + hitbox.h))
				{
					//the button is pressed
					edison_button_set_state(board->button_list[i], 0);
				}
			}
			break;
		}
	}
	return true;
	
}


