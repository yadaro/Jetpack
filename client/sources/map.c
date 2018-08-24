/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** map
*/

#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "client.h"

void		parse_map(client_t *client, char *str)
{
	int	i = 0;

	client->game.map.width = atoi(&str[i]);
	while (str[i] == ' ')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		i++;
	while (str[i] == ' ')
		i++;
	client->game.map.height = atoi(&str[i]);
	while ((str[i] >= '0') && (str[i] <= '9'))
		i++;
	while (str[i] == ' ')
		i++;
	client->game.map.map = strdup(&str[i]);
}
