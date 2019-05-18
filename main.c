#include "header.h"

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		sdl();
	}
	return 0;
}

int** build_grid(int size)
{
	int **grid = malloc(sizeof(int*) * size);
	int i, j;

	for (i = 0; i < size; i++)
		grid[i] = malloc(sizeof(int) * size);
	return grid;
}

void sdl(void)
{
	   if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
	int ** grid = build_grid(25);

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		draw_grid(renderer, grid, 25, 20);
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
			free(grid);
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
}
void draw_grid(SDL_Renderer* renderer,int **grid, int size, int delta)
{
	int i, j;
	int pi_x, pf_x, pi_y,pf_y;
	float a = 35 * M_PI / 180;
	float b = 45 * M_PI / 180;

	for (i = 0; i < size ; i++)
	{
		for (j = 0; j < size; j++)
		{
			pi_x = i*delta;
			pf_x = (i + 1)*delta;
			pi_y = j * delta;
			pf_y = (j + 1) * delta;
			if (i < size - 1)
				SDL_RenderDrawLine(renderer,
				250+ pi_x * cos(a)  - pi_y * sin(a),
						   50+ (pi_x * sin(a)  + pi_y * cos(a)) * cos(b),
				250+pf_x * cos(a)  - pi_y * sin(a),
						   50+ (pf_x * sin(a)  + pi_y * cos(a)) * cos(b));
			if (j < size - 1)
			SDL_RenderDrawLine(renderer,
				250 +pi_x * cos(a)  - pi_y * sin(a),
					   50 +(pi_x * sin(a)  + pi_y * cos(a))* cos(b),
				250 +pi_x * cos(a)  - pf_y * sin(a),
					   50 + (pi_x * sin(a)  + pf_y * cos(a)) * cos(b));
		}
	}
}
