/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** cSFML
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Event.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "csfml.h"
#include "display.h"
#include "client.h"
#include "print.h"

static void		crop_sprites(client_t *c)
{
	sfIntRect	pos_box = {0, 480, SIZE_UNIT, SIZE_UNIT};
	sfIntRect	rect_bg = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

	c->sfml.background = sfSprite_copy(c->sfml.sprite_map);
	sfSprite_setTextureRect(c->sfml.background, rect_bg);
	for (int i = 0; i < 6; i++)
		c->sfml.coin[i] = sfSprite_copy(c->sfml.sprite_map);
	for (int i = 0; i < 6; i++)
		c->sfml.elec[i] = sfSprite_copy(c->sfml.sprite_map);
	c->sfml.player = sfSprite_copy(c->sfml.sprite_map);
	c->sfml.enemy = sfSprite_copy(c->sfml.sprite_map);
	for (int i = 0; i < 14; i++) {
		if (i < 6)
			sfSprite_setTextureRect(c->sfml.coin[i], pos_box);
		if ((i >= 6) && (i < 12))
			sfSprite_setTextureRect(c->sfml.elec[i - 6], pos_box);
		if (i == 12)
			sfSprite_setTextureRect(c->sfml.player, pos_box);
		if (i == 13)
			sfSprite_setTextureRect(c->sfml.enemy, pos_box);
		pos_box.left = i * SIZE_UNIT + SIZE_UNIT;
	}
}

int			init_graph(client_t *c)
{
	sfVideoMode	mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
	sfTexture	*texture_map;

	c->sfml.win = sfRenderWindow_create(mode, "Jetpack2Tek3",
					sfClose, NULL);
	if (!c->sfml.win)
		return (print_error("Can't create a cSFML RenderWindow."));
	sfRenderWindow_setFramerateLimit(c->sfml.win, 60);
	sfRenderWindow_clear(c->sfml.win, sfBlack);
	c->sfml.font = sfFont_createFromFile("./resources/fonts/arial.ttf");
	if (!c->sfml.font)
		return (print_error("Can't set arial.ttf cSFML Font."));
	texture_map = sfTexture_createFromFile("./resources/textures.png",
					NULL);
	if (!texture_map)
		return (print_error("Can't set the cSFML Texture Map."));
	c->sfml.sprite_map = sfSprite_create();
	sfSprite_setTexture(c->sfml.sprite_map, texture_map, true);
	crop_sprites(c);
	return (1);
}

static bool		check_event(client_t *c)
{
	sfEvent		event;

	while (sfRenderWindow_pollEvent(c->sfml.win, &event))
		if (event.type == sfEvtClosed) {
			sfRenderWindow_close(c->sfml.win);
			c->game.run = false;
			return (false);
		} else if (event.type == sfEvtKeyPressed) {
			if ((event.key.code == sfKeyEscape) ||
			(event.key.code == sfKeyQ)) {
				sfRenderWindow_close(c->sfml.win);
				c->game.run = false;
				return (false);
			}
			else if (event.key.code == sfKeySpace) {
				dprintf(c->co.socket, "FIRE 1\n");
				c->game.player.fire = true;
			}
		} else if (event.type == sfEvtKeyReleased)
			if (event.key.code == sfKeySpace) {
				dprintf(c->co.socket, "FIRE 0\n");
				c->game.player.fire = false;
			}
	return (true);
}

void			csfml_game_loop(client_t *c)
{
	while ((c->game.run) && (sfRenderWindow_isOpen(c->sfml.win))) {
		sfRenderWindow_clear(c->sfml.win, sfBlack);
		if (!check_event(c))
			break;
		display_game(c);
		sfRenderWindow_display(c->sfml.win);
		usleep((1000 / 200) * 1000);
	}
}

void			csfml_free(client_t *c)
{
	sfFont_destroy(c->sfml.font);
	for (int i = 0; i < 6; i++)
		sfSprite_destroy(c->sfml.coin[i]);
	for (int i = 0; i < 6; i++)
		sfSprite_destroy(c->sfml.elec[i]);
	sfSprite_destroy(c->sfml.player);
	sfSprite_destroy(c->sfml.enemy);
	sfSprite_destroy(c->sfml.sprite_map);
	sfRenderWindow_destroy(c->sfml.win);
}
