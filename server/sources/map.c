/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** map.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "tools.h"
#include "error.h"
#include "print.h"


static bool		check_map(char *line)
{
	int		i = 0;

	while (line[i]) {
		if (line[i] == '_' ||
		line[i] == 'c' ||
		line[i] == 'e' ||
		line[i] == '\n')
			++i;
		else
			return (false);
	}
	return (true);
}

static char		**alloc_map(map_t *map)
{
	if (map->map == NULL)
		return ((char **)malloc(sizeof(char *) *
					(unsigned int)
					(map->y + 2)));
	else
		return ((char **)realloc(map->map,
					sizeof(char *) * (unsigned int)
					(map->y + 2)));
}

static bool		fill_map(FILE *file, server_t *srv)
{
	char		*line = NULL;
	ssize_t		buffsize = 0;
	size_t		len = (size_t)buffsize;

	if (!(buffsize = getline(&line, &len, file)) ||
	!(check_map(line)))
		return (false);
	srv->map.x = (unsigned long)buffsize;
	srv->map.y = 0;
	while ((buffsize = getline(&line, &len, file)) != -1) {
		if ((check_map(line) == false) ||
		((srv->map.map = alloc_map(&srv->map)) == NULL) ||
		(strlen(line) != srv->map.x))
			return (false);
		srv->map.map[srv->map.y] = strndup(line, srv->map.x - 1);
		srv->map.y++;
	}
	if (srv->map.map != NULL)
		srv->map.map[srv->map.y] = NULL;
	return (true);
}

bool			get_map(char *map_path, server_t *srv)
{
	FILE		*file;

	file = fopen(map_path, "r");
	if (file == NULL)
		return (false);
	srv->map.map = NULL;
	if (!fill_map(file, srv))
		return (false);
	if (fclose(file) != 0)
		return (false);
	return (true);
}
