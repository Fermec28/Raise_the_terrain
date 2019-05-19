#include "header.h"


void rot_transform(Point ***grid, size_grid size, int angle, char axis)
{
	Point aux;
	int i, j;
	float a = angle * M_PI / 180;

	for (i = 0; i < size.height ; i++)
	{
		for (j = 0; j < size.width; j++)
		{
			aux = (*grid)[i][j];
			if (axis == 'x')
			{
				(*grid)[i][j].y = aux.y * cos(a) - aux.z * sin(a);
				(*grid)[i][j].z = aux.y * sin(a) + aux.z * cos(a);
			}
			else if (axis == 'y')
			{
				(*grid)[i][j].x = aux.x * cos(a) + aux.z * sin(a);
				(*grid)[i][j].z = -aux.x * sin(a) + aux.z * cos(a);
			}
			else if (axis == 'z')
			{
				(*grid)[i][j].x = aux.x * cos(a) - aux.y * sin(a);
				(*grid)[i][j].y = aux.x * sin(a) + aux.y * cos(a);
			}
		}
	}
}


void calculate_range(Point **grid, size_grid *min_max, size_grid size)
{
	int i, j;

	min_max[0].width =  grid[0][0].x;
	min_max[0].height = grid[0][0].y;
	min_max[1].width = grid[0][0].x;
	min_max[1].height = grid[0][0].y;

	for (i = 0; i < size.height ; i++)
	{
		for (j = 0; j < size.width; j++)
		{
			if(grid[i][j].x < min_max[0].width)
				min_max[0].width =  grid[i][j].x;
			if(grid[i][j].y < min_max[0].height)
				min_max[0].height =  grid[i][j].y;
			if(grid[i][j].x > min_max[1].width)
				min_max[1].width =  grid[i][j].x;
			if(grid[i][j].x > min_max[1].height)
				min_max[1].height =  grid[i][j].y;
		}
	}
}
