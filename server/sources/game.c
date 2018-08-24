/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** game.c
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void	set_death(server_t *srv, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (fd == srv->player[i].id) {
			srv->player[i].dead = true;
		}
	}
}

void	set_score(server_t *srv, int fd, char c)
{
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (fd == srv->player[i].id)
			srv->player[i].score++;
		dprintf(srv->player[i].id, "COIN %d %d %d\n", fd,
			(int)srv->player[i].x, (int)srv->player[i].y);
	}
}

void	check_finish(server_t *srv)
{
	for (int i = 0; i < MAX_CLIENTS ; ++i)
		dprintf(srv->player[i].id, "FINISH -1\n");
	srv->end = true;
}

void	loop_game(server_t *srv, int fd, char *line)
{
	char    **tmp = srv->map.map;
	int d = 0;
	double y = 0;

	char **tab = str_to_wordtab(line, ' ');

	y = (srv->map.y / 2);
	while (srv->end != true) {
		for (int i = 0; i < MAX_CLIENTS; ++i) {
			srv->player[i].y = (srv->map.y - y) - 1;
			for (int j = 0; j < MAX_CLIENTS; ++j)
				dprintf(srv->player[j].id, "PLAYER %d %f %f %d\n" , srv->player[i].id,
				srv->player[i].x, srv->player[i].y, srv->player[i].score);
			if (tmp[(int)y][(int)srv->player[i].x] == 'e')
				set_death(srv, fd);
			if (tmp[(int)y][(int)srv->player[i].x] == 'c') {
				srv->player[i].score++;
				for (int j = 0; j < MAX_CLIENTS; ++j)
					dprintf(srv->player[j].id, "COIN %d %f %f\n", srv->player[i].id,
					srv->player[i].x, (srv->player[i].y ));
				}
			if (!strcmp(tab[0], "FIRE") && tab[1] != NULL ) {
				if (!strcmp(tab[1], "1"))
					srv->player[i].fire = true;
				else if (!strcmp(tab[1], "0"))
					srv->player[i].fire = false;
			}
			if (srv->player[i].dead == true)
				++d;
			if (srv->player[i].x == srv->map.x - 1) {
				printf("END\n");
				srv->end = true;
			}
			if (d == MAX_CLIENTS)
				check_finish(srv);
			if (srv->player[i].fire == true)
				y--;
			else
				y++;
			if (y < 0)
				y = 0;
			else if (y > srv->map.y - 1)
				y = srv->map.y - 1;
			set_delay(200);
			srv->player[i].x++;
		}
	}
}
