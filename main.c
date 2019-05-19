#include "header.h"


int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		size_grid size = get_size(argv[1]);
		Point **grid = build_grid(size.width, size.height);
		calculate_points(&grid, argv[1]);
		sdl(grid, size);
	}
	return 0;
}


void free_grid(Point **grid, size_grid size)
{
	int i, j;

	for (i = 0; i < size.height; i++)
	{
		free(grid[i]);
	}
	free(grid);
}
Point** build_grid(int width, int height)
{
	Point **grid = malloc(sizeof(Point*) * height);
	int i, j;

	for (i = 0; i < height; i++)
	{
		grid[i] = malloc(sizeof(Point) * width);
		if (grid[i] == NULL)
		{
			printf("No se pudo crear el espacio de memoria");
			exit(1);
		}
	}
	return grid;
}

void sdl(Point ** grid, size_grid size)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;

			while (!done)
			{
				SDL_Event event;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				draw_grid(renderer, grid, size);
				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					        free_grid(grid, size);
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window)
		{
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}
void draw_grid(SDL_Renderer* renderer,Point **grid, size_grid size)
{
	int i, j;

	for (i = 0; i < size.height ; i++)
	{
		for (j = 0; j < size.width; j++)
		{
			if (i < size.height - 1)
				SDL_RenderDrawLine(renderer,
						   grid[i][j].x,
						   grid[i][j].y,
						   grid[i][j + 1].x,
						   grid[i][j].y);
			if (j < size.width - 1)
				SDL_RenderDrawLine(renderer,
						   grid[i][j].x,
						   grid[i][j].y,
						   grid[i][j].x,
						   grid[i][j + 1].y);
		}
	}
}
