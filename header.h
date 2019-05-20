#ifndef _DEMO_H_
#define _DEMO_H_
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define M_PI 3.14159265358979323846
/**
 * struct size_grid - size of grid
 * @width: store the width of the window
 * @height: store the height of the window
 *
 * Description: structure to handle the size of window
 */
typedef struct size_grid
{
	int width;
	int height;

} size_grid;
/**
 * struct SDL_Instance - struct sdl
 * @window: Window to render
 * @renderer: Object to render
 *
 * Description: struncture organize sdl functionalities
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;
/**
 * struct point - Store pont on space
 * @x: value x axis
 * @y: value y axis
 * @z: value z axis
 *
 * Description: structure to store a point on the space
 */
typedef struct point
{
	int x;
	int y;
	int z;
} Point;
int get_num_lines(const char *filename);
int get_num_columns(const char *filename);
int init_instance(SDL_Instance *);
Point **build_grid(int, int);
size_grid get_size(const char *filename);
void draw_grid(SDL_Renderer *, Point **, size_grid, size_grid *min_max);
void sdl(Point **, size_grid, size_grid, size_grid *min_max);
void calculate_points(Point ***grid, const char *filename, size_grid delta);
void free_grid(Point **grid, size_grid size);
void rot_transform(Point ***grid, size_grid size, int angle, char axis);
void calculate_range(Point **grid, size_grid *min_max, size_grid size);
#endif
