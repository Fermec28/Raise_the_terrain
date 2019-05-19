#include "header.h"

void calculate_points (Point ***grid, const char *filename)
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
		printf("value of line %s\n", line);
		j = 0;
		line = strtok(line, " ");
		while( line != NULL )
		{
			printf("line %s -- i:%d ; j:%d\n", line,i,j);
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
 *
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
	return(lines);
}

/**
 * get_num_lines - get num of lines this will be the num of rows
 * @filename: path of the file
 * Return: num of lines
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
    while( line != NULL )
    {
        line = strtok(NULL, " ");
        num_columns++;
    }

    free(line);
    fclose(fp);
    return(num_columns);
}