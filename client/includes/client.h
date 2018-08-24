/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** client
*/

#pragma once
#include <stdbool.h>
#include <netinet/ip.h>
#include <SFML/Graphics.h>
#include <pthread.h>
#define BUFF_SIZE 8192

typedef struct			protoent *protoent_t;

typedef struct			connection_s {
	struct sockaddr_in	s_in;
	int			socket;
	unsigned short		port;
	char			pad_1[2];
	char			*ip;
}				connection_t;

typedef struct			map_s {
	int			width;
	int			height;
	char			*map;
}				map_t;

typedef struct			player_s {
	double			posX;
	double			posY;
	unsigned int		id;
	unsigned int		score;
	bool			fire;
	char			pad_2[7];
}				player_t;

typedef struct			game_s {
	player_t		player;
	player_t		enemy;
	map_t			map;
	bool			run;
	char			pad_3[7];
}				game_t;

typedef struct			csfml_s {
	sfRenderWindow		*win;
	sfSprite		*sprite_map;
	sfFont			*font;
	sfSprite		*background;
	sfSprite		*coin[6];
	sfSprite		*elec[6];
	sfSprite		*player;
	sfSprite		*enemy;
	int			scroll;
	char			pad_4[4];
}				csfml_t;

typedef struct			client_s {
	game_t			game;
	connection_t		co;
	csfml_t			sfml;
	pthread_t		thread;
	bool			connected;
	char			pad_5[7];
}				client_t;
