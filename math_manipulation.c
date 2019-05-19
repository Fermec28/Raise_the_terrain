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
