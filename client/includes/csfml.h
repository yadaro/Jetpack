/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** csfml
*/

#pragma once
#include <SFML/Graphics.h>
#include "client.h"
static const int WINDOW_WIDTH = 1920;
static const int WINDOW_HEIGHT = 480;
static const int SIZE_UNIT = 48;

int		init_graph(client_t *c);
void		csfml_game_loop(client_t *c);
void		csfml_free(client_t *c);
