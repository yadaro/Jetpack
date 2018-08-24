/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Parser cmd client
*/

#include <stdlib.h>
#include <stdio.h>
#include "csfml.h"
#include "colors.h"
#include "client.h"
#include "parse_net.h"

void		parse_finish(client_t *c, char *str)
{
	int	i = 6;

	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		printf("%sNobody wins.%s\n", C_YELLOW, C_CLEAR);
	else if (c->game.player.id == (unsigned int) atoi(&str[i]))
		printf("%sYou are the winner !%s\n", C_GREEN, C_CLEAR);
	else
		printf("%sYou lose the game !%s\n", C_PURPLE, C_CLEAR);
	c->game.run = false;
}

static void	parse_player_end(client_t *c, char *str, int i)
{
	while (((str[i] >= '0') && (str[i] <= '9')) || (str[i] == '.'))
		i++;
	while (str[i] == ' ')
		i++;
	if (c->game.player.id == (unsigned int) atoi(&str[6]))
		c->game.player.posY = atof(&str[i]);
	else if (c->game.enemy.id == (unsigned int) atoi(&str[6]))
		c->game.enemy.posY = atof(&str[i]);
	while (((str[i] >= '0') && (str[i] <= '9')) || (str[i] == '.'))
		i++;
	while (str[i] == ' ')
		i++;
	if (c->game.player.id == (unsigned int) atoi(&str[6]))
		c->game.player.score = (unsigned int) atoi(&str[i]);
	else if (c->game.enemy.id == (unsigned int) atoi(&str[6]))
		c->game.enemy.score = (unsigned int) atoi(&str[i]);
}

void		parse_player(client_t *c, char *str)
{
	int	i = 6;

	if ((c->game.player.id != (unsigned int) atoi(&str[i]))
			&& (c->game.enemy.id == 0))
		c->game.enemy.id = (unsigned int) atoi(&str[i]);
	while (str[i] == ' ')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		i++;
	while (str[i] == ' ')
		i++;
	if (c->game.player.id == (unsigned int) atoi(&str[6]))
		c->game.player.posX = atof(&str[i]);
	else if (c->game.enemy.id == (unsigned int) atoi(&str[6]))
		c->game.enemy.posX = atof(&str[i]);
	if (atoi(&str[i]) > 5)
		if ((c->game.map.width * SIZE_UNIT > WINDOW_WIDTH) &&
		(c->sfml.scroll < c->game.map.width * SIZE_UNIT - WINDOW_WIDTH))
			c->sfml.scroll = (int)((atof(&str[i]) - 5) * SIZE_UNIT);
	parse_player_end(c, str, i);
}

void		parse_coin(client_t *c, char *str)
{
	int	i = 4;
	int	x = 0;
	int	y = 0;

	while (str[i] == ' ')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		i++;
	while (str[i] == ' ')
		i++;
	x = atoi(&str[i]);
	while ((str[i] >= '0') && (str[i] <= '9'))
		i++;
	while (str[i] == ' ')
		i++;
	y = ((atoi(&str[i]) - (c->game.map.height - 1)) * (-1));
	c->game.map.map[(y * (c->game.map.width) + x)] = '_';
}
