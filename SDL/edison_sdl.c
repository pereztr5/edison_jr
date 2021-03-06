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
	edison_potentiometer *edison_pot;
	SDL_Point board_size;
	SDL_Window* window;
	SDL_Surface* board_surface;
	SDL_Renderer* renderer;
	edison_texture* texture_cache[EDISON_TEXTURE_MAX];
	uint texture_count;

	char* base_path;
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
		board->base_path = SDL_GetBasePath();
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
	board->texture_count = 0;
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
	char *env_path;
	char temp_char[2];
	char path[1000] = "";
	bool nochar;
	int i, j;

	borders.x = 20;
	borders.y = 45;
	borders.w = 500;
	borders.h = 200;

	env_path = getenv("EDISON_PATH");
	
	strcat(path, env_path);
	strcat(path, "display.bmp");
	temp_surface = SDL_LoadBMP(path);

	if(temp_surface == NULL)
	{
		printf("%s\n", SDL_GetError());
	}
	else
	{
		temp_texture = SDL_CreateTextureFromSurface(board -> renderer, temp_surface);
		SDL_RenderCopy(board -> renderer, temp_texture, NULL, &borders);
		SDL_FreeSurface(temp_surface);
	}

	borders.x = 34;
	borders.y = 62;
	borders.w = 16;
	borders.h = 26;

	temp_char[1] = '\0';

	for(i = 0; i < MAX_LINES; i++)
	{
		for(j = 0; j < MAX_CHARS; j++)
		{
			memset(path, 0, 1000);
			nochar = false;
			strcat(path, env_path);
			temp_char[0] = board -> edison_lcd -> display_content[MAX_CHARS * i + j];

			if( ( temp_char[0] >= 48 && temp_char[0] <= 57 ) || ( temp_char[0] >= 97 && temp_char[0] <= 122 ) )
			{
				strcat(path, temp_char);
				strcat(path, ".bmp");
				temp_surface = SDL_LoadBMP(path);
			}
			else
			{
				temp_surface = NULL;
				nochar = true;
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
			SDL_FreeSurface(temp_surface);
		}
		borders.x = 34;
		borders.y += 35;
	}

	SDL_DestroyTexture(temp_texture);
	return;
}

void edison_render_potentiometer(edison_board* board)
{
	SDL_Rect borders, control;
	SDL_Texture *temp_texture;
	SDL_Surface *temp_surface;
	char *env_path;
	char path[1000] = "";

	env_path = getenv("EDISON_PATH");
	strcat(path, env_path);
	strcat(path, "potentiometer.bmp");
	temp_surface = SDL_LoadBMP(path);
	memset(path, 0, 1000);

	borders.x = 20;
	borders.y = 275;
	borders.w = 40;
	borders.h = 200;

	control.x = board -> edison_pot -> hitbox.x;
	control.w = board -> edison_pot -> hitbox.w;
	control.h = board -> edison_pot -> hitbox.h;

	

	switch(board -> edison_pot -> current_position)
	{
		case 1:
			control.y = 450;
			break;
		case 2:
			control.y = 431;
			break;
		case 3:
			control.y = 412;
			break;
		case 4:
			control.y = 393;
			break;
		case 5:
			control.y = 374;
			break;
		case 6:	
			control.y = 355;
			break;
		case 7:
			control.y = 338;
			break;
		case 8:
			control.y = 319;
			break;
		case 9:
			control.y = 300;
			break;
		default:
			control.y = 280;
			break;
	}

	board -> edison_pot -> hitbox.y = control.y;
				

	if(temp_surface == NULL)
	{
		printf("%s\n", SDL_GetError());
	}
	else
	{
		temp_texture = SDL_CreateTextureFromSurface(board -> renderer, temp_surface);
		SDL_RenderCopy(board -> renderer, temp_texture, NULL, &borders);
	}

	SDL_SetRenderDrawColor(board -> renderer, 255, 200, 0, 255);
	SDL_RenderFillRect(board -> renderer, &board -> edison_pot -> hitbox);

	SDL_FreeSurface(temp_surface);
	SDL_DestroyTexture(temp_texture);
	return;
}

void edison_add_potentiometer(edison_board *board, edison_potentiometer *edison_pot)
{
	board -> edison_pot = edison_pot;
	return;
}

edison_texture* edison_load_texture(edison_board* board, char* texture)
{
	//printf("Attempting to load %s\n", texture);
	//printf("base path is %s\n", board->base_path);
	char* path = (char*)malloc(sizeof(char) * 512);
	strcpy(path, getenv("EDISON_PATH"));
	strcat(path, texture);
	
	//printf("image is at loc: \'%s'\n", path);

	if(board->texture_count >= EDISON_TEXTURE_MAX)
	{
		//printf("Cannot load texture into cache: %s, the cache is full\n", path);
		return NULL;
	}
	// look in cache

	//printf("looking for texture %s in cache...\n", path);
	int i;
	for(i = 0; i < board->texture_count; i++)
	{
		edison_texture* t = board->texture_cache[i];
		if(strcmp(t->name, path) == 0)
		{
			return t;
		}
	}

	// Not in cache, so load from disk
	//printf("Couldn't find in cache, loading from disk...\n");
	edison_texture* tex = (edison_texture*)malloc(sizeof(edison_texture));
	tex->name = path;

	//printf("Loading file..\n");
	SDL_Surface* temp_surface = SDL_LoadBMP(path);

	if(!temp_surface)
	{
		//printf("%s\n", SDL_GetError());
		return NULL;
	} 
	else
	{
		//printf("Creating texture from image!\n");
		SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(board->renderer, temp_surface); 

		if(temp_texture == NULL)
		{
			printf("%s\n", SDL_GetError());
			//free(tex);
			tex = NULL;
		}
		else
		{
			tex->texture = temp_texture;
		}
		SDL_FreeSurface(temp_surface);
	}
	board->texture_cache[board->texture_count] = tex;
	board->texture_count++;
	return tex;
}

void edison_render_texture(edison_board* board, edison_texture* texture, SDL_Rect* src, SDL_Rect* dst)
{
	if(texture != NULL)
	{
		SDL_RenderCopy(board->renderer, texture->texture, src, dst);
	}
}

/**
 * Renders the given board
 */
void edison_render(edison_board* board)
{
	SDL_SetRenderDrawColor(board->renderer, 0, 50, 0, 0);
	SDL_RenderClear(board->renderer);

	edison_texture* bg = edison_load_texture(board, "images/bg.bmp");
	if(bg != NULL)
		SDL_RenderCopy(board->renderer, bg->texture, NULL, NULL);
	edison_render_leds(board);
	edison_render_buttons(board);
	edison_render_sevensegs(board);
	edison_render_dipswitches(board);
	edison_render_lcd_display(board);
	edison_render_potentiometer(board);
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

			// Potentiometer

			SDL_Rect hitbox = board -> edison_pot -> hitbox;

			if(x > hitbox.x && x < (hitbox.x + hitbox.w) && y > hitbox.y && y < (hitbox.y + hitbox.h))
			{
				board -> edison_pot -> potentiometer_mode = true;

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

			if(board -> edison_pot -> potentiometer_mode)
			{
				board -> edison_pot -> potentiometer_mode = 0;	
			}

			break;

			case SDL_MOUSEMOTION:

			if(board -> edison_pot -> potentiometer_mode)
			{
				SDL_GetMouseState(&x, &y);

				if(y > 431)
				{
					board -> edison_pot -> current_position = 1;
				}
				else if(y > 412)
				{
					board -> edison_pot -> current_position = 2;	
				}
				else if(y > 393)
				{
					board -> edison_pot -> current_position = 3;	
				}
				else if(y > 374)
				{
					board -> edison_pot -> current_position = 4;	
				}
				else if(y > 355)
				{
					board -> edison_pot -> current_position = 5;	
				}
				else if(y > 338)
				{
					board -> edison_pot -> current_position = 6;	
				}
				else if(y > 319)
				{
					board -> edison_pot -> current_position = 7;	
				}
				else if(y > 300)
				{
					board -> edison_pot -> current_position = 8;	
				}
				else if(y > 280)
				{
					board -> edison_pot -> current_position = 9;	
				}
				else
				{
					board -> edison_pot -> current_position = 10;	
				}
			}
			break;


		}
	}
	return true;
	
}


