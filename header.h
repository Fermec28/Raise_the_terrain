#ifndef _DEMO_H_
#define _DEMO_H_
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define M_PI 3.14159265358979323846
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

int init_instance(SDL_Instance *);
int** build_grid(int);
void draw_grid(SDL_Renderer* renderer,int **grid, int size, int delta);
void sdl (void);
#endif
