#include "header.h"
/**
 * main - Entry point
 * @argc: count of arguments
 * @argv: value of arguments
 * Return: alway success
 */
int main(int argc, char *argv[])
{
	size_grid size;

	Point **grid;
	size_grid SIZE_WINDOW = {640, 480}, delta;
	size_grid min_max[2];

	if (argc == 2)
	{
		size = get_size(argv[1]);
		grid = build_grid(size.width, size.height);
		delta.width = SIZE_WINDOW.width / size.width;
		delta.height = SIZE_WINDOW.height / size.height;
		calculate_points(&grid, argv[1], delta);
		rot_transform(&grid, size, -35, 'z');
		rot_transform(&grid, size, 45, 'x');
		sdl(grid, size, SIZE_WINDOW, min_max);
	}
	return (0);
}
/**
 * free_grid -  free the grid
 * @grid: grid to be freeded
 * @size: size of the grid
 */
void free_grid(Point **grid, size_grid size)
{
	int i, j;

	for (i = 0; i < size.height; i++)
	{
		free(grid[i]);
	}
	free(grid);
}
/**
 * build_grid - create the required space on memory
 * @width: width of the grid
 * @height: height of the grid
 * Return: Array of Pointers
 */
Point **build_grid(int width, int height)
{
	Point **grid = malloc(sizeof(Point *) * height);
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
	return (grid);
}
/**
 * sdl - sdl funcitionality
 * @grid: all points
 * @size: size of the grid
 * @S_WINDOW: size of the windoe
 * @min_ma: range of the points
 */
void sdl(Point **grid, size_grid size, size_grid S_WINDOW, size_grid *min_ma)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window *window = NULL;
		SDL_Renderer *renderer = NULL;

		if (SDL_CreateWindowAndRenderer(S_WINDOW.width,
						 S_WINDOW.height, 0,
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
				draw_grid(renderer, grid, size, min_ma);
				SDL_RenderPresent(renderer);
				handle_events(event, grid, size, &done);
			}
		}

		if (renderer)
			SDL_DestroyRenderer(renderer);
		if (window)
			SDL_DestroyWindow(window);
	}
	SDL_Quit();
}
/**
 * draw_grid - Draw the gride on  window
 * @renderer: Object to print the objects
 * @grid: array of pointers
 * @size: size of the grud
 * @min_max: range of the points
 */
void draw_grid(SDL_Renderer *renderer, Point **grid, size_grid size
	       , size_grid *min_max)
{
	int i, j;
	float scale_x;
	float scale_y;

	calculate_range(grid, min_max, size);
	scale_x = (min_max[1].width - min_max[0].width);
	scale_y = (min_max[1].height - min_max[0].height);
	for (i = 0; i < size.height ; i++)
	{
		for (j = 0; j < size.width; j++)
		{
			if (i < size.height - 1)
				SDL_RenderDrawLine(renderer,
				   640 *  (grid[i][j].x  - min_max[0].width) / scale_x,
				   480 * (grid[i][j].y - min_max[0].height) / scale_y,
				   640 *  (grid[i + 1][j].x - min_max[0].width) / scale_x,
				   480 * (grid[i + 1][j].y - min_max[0].height) / scale_y);
			if (j < size.width - 1)
				SDL_RenderDrawLine(renderer,
				   640  * (grid[i][j].x - min_max[0].width) / scale_x,
				   480 * (grid[i][j].y - min_max[0].height) / scale_y,
				   640  * (grid[i][j + 1].x - min_max[0].width) / scale_x,
				   480 * (grid[i][j + 1].y - min_max[0].height) / scale_y);
		}
	}
}
