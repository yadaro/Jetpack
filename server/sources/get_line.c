/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** get_line
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

static void	get_line_third(char **line_2, char **line, int *i)
{
	*line = malloc(sizeof(char) * (strlen(*line_2) + 1));
	strncpy(*line, *line_2, strlen(*line_2));
	(*line)[strlen(*line_2)] = 0;
	free(*line_2);
	++(*i);
}

static void	get_line_second(char **line_2, char **line, char buf[])
{
	(*line_2) = malloc(sizeof(char) * (strlen(*line) + 2));
	strncpy((*line_2), *line, strlen(*line));
	strncpy((*line_2) + strlen(*line), buf, 1);
	(*line_2)[strlen(*line) + 1] = 0;
	free((*line));
}

static void	get_line_first(char **line_2, char buf[])
{
	(*line_2) = malloc(sizeof(char) * 2);
	strncpy((*line_2), buf, 1);
	(*line_2)[1] = 0;
}

static char	*save_me(void)
{
	char	*line = malloc(sizeof(char));

	line[0] = 0;
	return (line);
}

char	*get_line(int fd)
{
	char	buf[1];
	char	*line = NULL;
	char	*line_2 = NULL;
	int	i = 0;
	int	len = 0;

	while ((len = read(fd, buf, 1)) && buf[0] != '\n') {
		if (line == NULL) {
			get_line_first(&line_2, buf);
		} else
			get_line_second(&line_2, &line, buf);
		get_line_third(&line_2, &line, &i);
	}
	if (len == 0)
		return (NULL);
	else if (line == NULL)
		return (save_me());
	line[i] = 0;
	return (line);
}
