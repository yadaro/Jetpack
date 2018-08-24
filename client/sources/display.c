/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** csfml Display functions
*/

#include <SFML/Graphics.h>
#include <memory.h>
#include "display.h"
#include "client.h"
#include "csfml.h"

static void		display_players(client_t *c)
{
	sfVector2f	player_pos = {(float)c->game.player.posX * SIZE_UNIT -
				c->sfml.scroll, ((WINDOW_HEIGHT - SIZE_UNIT)
				- (float)c->game.player.posY * SIZE_UNIT)};
	sfVector2f	enemy_pos = {(float)c->game.enemy.posX * SIZE_UNIT -
				c->sfml.scroll, ((WINDOW_HEIGHT - SIZE_UNIT)
				- (float)c->game.enemy.posY * SIZE_UNIT)};
	sfSprite_setPosition(c->sfml.player, player_pos);
	sfSprite_setPosition(c->sfml.enemy, enemy_pos);
	sfRenderWindow_drawSprite(c->sfml.win, c->sfml.enemy, NULL);
	sfRenderWindow_drawSprite(c->sfml.win, c->sfml.player, NULL);
}

static void		display_map(client_t *c)
{
	for (int i = 0; i < (int)strlen(c->game.map.map); i++) {
		sfVector2f pos = {((i % c->game.map.width) * SIZE_UNIT)
				- c->sfml.scroll,
				(i / c->game.map.width) * SIZE_UNIT};
		if (c->game.map.map[i] == 'e') {
			sfSprite_setPosition(c->sfml.elec[0], pos);
			sfRenderWindow_drawSprite(c->sfml.win,
						c->sfml.elec[0], NULL);
		} else if (c->game.map.map[i] == 'c') {
			sfSprite_setPosition(c->sfml.coin[0], pos);
			sfRenderWindow_drawSprite(c->sfml.win,
						c->sfml.coin[0], NULL);
		}
	}
}

void			display_game(client_t *c)
{
	sfRenderWindow_drawSprite(c->sfml.win, c->sfml.background, NULL);
	display_map(c);
	display_players(c);
}
