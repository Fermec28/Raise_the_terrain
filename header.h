#ifndef _DEMO_H_
#define _DEMO_H_
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define M_PI 3.14159265358979323846

typedef struct size_grid
{
	int width;
	int height;

} size_grid;

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

typedef struct point
{
	int x;
	int y;
	int z;
} Point;
int get_num_lines(const char *filename);
int get_num_columns(const char *filename);
int init_instance(SDL_Instance *);
Point** build_grid(int, int);
size_grid get_size(const char *filename);
void draw_grid(SDL_Renderer* renderer,Point **grid, size_grid size);
void sdl(Point ** grid, size_grid size);
void calculate_points (Point ***grid, const char *filename);
void free_grid(Point **grid, size_grid size);
#endif
