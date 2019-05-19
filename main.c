#include "header.h"
int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		size_grid size = get_size(argv[1]);
		Point **grid = build_grid(size.width, size.height);
		size_grid SIZE_WINDOW = {640, 480}, delta;
		size_grid min_max[2];

		delta.width = SIZE_WINDOW.width / size.width;
		delta.height = SIZE_WINDOW.height / size.height;
		calculate_points(&grid, argv[1], delta);
		rot_transform(&grid, size, -35, 'z');
		rot_transform(&grid, size, 45, 'x');
		calculate_range(grid, min_max , size);
		sdl(grid, size, SIZE_WINDOW, min_max);
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

void sdl(Point **grid, size_grid size, size_grid SIZE_WINDOW, size_grid *min_max)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(SIZE_WINDOW.width,
						 SIZE_WINDOW.height, 0,
						 &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;

			while (!done)
			{
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0,
						       SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255,
						       SDL_ALPHA_OPAQUE);
				draw_grid(renderer, grid, size, min_max);
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

void draw_grid(SDL_Renderer *renderer,Point **grid, size_grid size
	       , size_grid *min_max)
{
	int i, j;
	float scale_x =  5;//(min_max[1].width - min_max[0].width);
	float scale_y =  5;//(min_max[1].height - min_max[0].height);

	for (i = 0; i < size.height ; i++)
	{
		for (j = 0; j < size.width; j++)
		{
			if (i < size.height - 1)
				SDL_RenderDrawLine(renderer,
				   size.width / 2 + scale_x *  (grid[i][j].x - min_max[0].width)/10 ,
				   size.height / 2 + scale_y * (grid[i][j].y - min_max[0].height)/10 ,
				   size.width / 2 + scale_x *  (grid[i + 1][j].x - min_max[0].width)/10 ,
				   size.height / 2 + scale_y * (grid[i + 1][j].y - min_max[0].height)/10);
			if (j < size.width - 1)
				SDL_RenderDrawLine(renderer,
				   size.width / 2 + scale_x  * (grid[i][j].x - min_max[0].width)/10 ,
				   size.height / 2 + scale_y * (grid[i][j].y - min_max[0].height)/10 ,
				   size.width / 2 + scale_x  * (grid[i][j + 1].x - min_max[0].width)/10 ,
				   size.height / 2 + scale_y * (grid[i][j + 1].y - min_max[0].height) / 10) ;
		}
	}
}
