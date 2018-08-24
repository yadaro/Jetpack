/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Init
*/

#include <stdbool.h>
#include <stddef.h>
#include <printf.h>
#include "init.h"
#include "client.h"
#include "network.h"
#include "print.h"

static void	initStruct(client_t *c)
{
	c->co.socket = 0;
	c->connected = false;
	c->game.map.width = 0;
	c->game.map.height = 0;
	c->game.map.map = NULL;
	c->game.run = false;
	c->game.player.posX = 0;
	c->game.player.posY = 0;
	c->game.player.id = 0;
	c->game.player.score = 0;
	c->game.player.fire = false;
	c->game.enemy.posX = 0;
	c->game.enemy.posY = 0;
	c->game.enemy.id = 0;
	c->game.enemy.score = 0;
	c->game.enemy.fire = false;
	c->sfml.scroll = 0;
}

bool		init(client_t *client)
{
	initStruct(client);
	if (init_network(&client->co) == -1)
		return (false);
	client->connected = true;
	if (!protocol_to_start(client)) {
		print_error("Protocol Error : Recv failed.");
		return (false);
	}
	return (true);
}
