#include "edison_sdl.h"
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
			SDL_Point size;
			size.x = size_x;
			size.y = size_y;
			board->board_surface = SDL_GetWindowSurface(board->window);
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
	SDL_DestroyWindow(board->window);
	SDL_Quit();
	free(board->led_list);
	//delete board->switch_list;
	free(board);
}

/**
 * Adds an LED to the board
 */
void edison_add_led(edison_board* board, edison_led* led)
{
	if(board->led_count < 100)
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
		SDL_Rect rect;
		edison_led* led = board->led_list[i];

		rect.x = led->position.x;
		rect.y = led->position.y;
		rect.w = 35;
		rect.h = 35;

		SDL_FillRect(board->board_surface, &rect, SDL_MapRGB(board->board_surface->format, led->color.r, led->color.g, led->color.b));	
	}
}

/**
 * Renders the given board
 */
void edison_render(edison_board* board)
{
	edison_render_leds(board);
	SDL_UpdateWindowSurface(board->window);
}

void edison_poll_events()
{
	SDL_Event e;
	
}