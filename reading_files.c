#include "header.h"
/**
 * calculate_points - calculate all points, read z points and calculate
 * x e y
 * @grid: allpoints
 * @filename: path to the filse store the z points
 * @delta: diference to create points
 */
void calculate_points(Point ***grid, const char *filename, size_grid delta)
{
	FILE *fp;
	char *line = NULL;
	ssize_t read;
	size_t len = 0;
	int i = 0, j;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	while ((read = getline(&line, &len, fp) != -1))
	{
		j = 0;
		line = strtok(line, " ");
		while (line != NULL)
		{
			(*grid)[i][j].x = delta.width * j;
			(*grid)[i][j].y = delta.height * i;
			(*grid)[i][j].z = atoi(line);
			line = strtok(NULL, " \n");
			j++;
		}
		i++;
	}
	free(line);
	fclose(fp);
}

/**
 * read_file - read a file sended
 * @filename: file to read
 * Return: number of characters readed
 */
size_grid get_size(const char *filename)
{
	size_grid size;

	size.width = get_num_columns(filename);
	size.height = get_num_lines(filename);
	return (size);
}

/**
 * get_num_lines - get num of lines this will be the num of rows
 * @filename: path of the file
 * Return: num of lines
 */
int get_num_lines(const char *filename)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int lines = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	while ((read = getline(&line, &len, fp) != -1))
	{
		lines++;
	}
	free(line);
	fclose(fp);
	return (lines);
}

/**
 * get_num_columns - get num of lines this will be the num of rows
 * @filename: path of the file
 * Return: num of columns
 */
int get_num_columns(const char *filename)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int num_columns = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	line = strtok(line, " ");
	while (line != NULL)
	{
		line = strtok(NULL, " ");
		num_columns++;
	}

	free(line);
	fclose(fp);
	return (num_columns);
}
