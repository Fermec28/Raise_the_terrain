#include "header.h"
/**
 * handle_events - listen events
 * @event: sdlobject events
 * @grid: Points
 * @size: size of grid
 * @d: done flag to stop the program
 */
void handle_events(SDL_Event event, Point **grid, size_grid size, SDL_bool *d)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			*d = SDL_TRUE;
			free_grid(grid, size);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				rot_transform(&grid, size, -1, 'y');
				break;
			case SDLK_RIGHT:
				rot_transform(&grid, size, 1, 'y');
				break;
			case SDLK_UP:
				rot_transform(&grid, size, 1, 'x');
				break;
			case SDLK_DOWN:
				rot_transform(&grid, size, -1, 'x');
				break;
			case 27:
				*d = SDL_TRUE;
				free_grid(grid, size);
				break;
			default:
				break;
			}
		}
	}
}
