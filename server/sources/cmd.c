/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** cmd.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

void	print_map(server_t *srv, int fd)
{
	map_t tmp = srv->map;
	char *map = NULL;
	char *final = NULL;

	map = malloc(sizeof(char) * (srv->map.x + 1));
	final = malloc(sizeof(char) * (srv->map.x * srv->map.y + 1));
	final[0] = 0;
	for (int i = 0; i < MAX_CLIENTS; i++)
		if (srv->player[i].req_map == false && srv->player[i].req_id == true) {
			while (*(tmp.map)) {
				memset(map, 0, strlen(map));
				map = strcpy(map, *(tmp.map));
				*(tmp.map)++;
				final = strcat(final, map);
			}
			dprintf(fd, "MAP %lu %lu %s\n", tmp.x - 1, tmp.y + 1, final);
			srv->player[i].req_map = true;
		}
	free(map);
	free(final);
}

void	set_id(server_t *srv, int fd)
{
	bool found = false;

	for (int i = 0; i < MAX_CLIENTS; i++)
		if (srv->player[i].id == fd)
			found = true;
	if (!found)
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if (srv->player[i].id == 0) {
				srv->player[i].id = fd;
				srv->player[i].req_id = true;
				dprintf(fd, "ID %d\n", srv->player[i].id);
				break;
			}
		}
}

void    set_ready(server_t * srv, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
		// if (srv->player[i].id == fd)
			if (srv->player[i].req_id == true &&
			srv->player[i].req_map == true) {
				srv->player[i].ready = true;
				// wait_ready(srv);
			}
}

void	set_jetpack(server_t *srv, int fd)
{
	if (srv->start == true) {
		for (int i = 0; i < MAX_CLIENTS; ++i) {
			if (fd == srv->player[i].id) {
				if (srv->player[i].fire == false)
					srv->player[i].fire = true;
				else
					srv->player[i].fire = false;
				dprintf(fd, "FIRE %d\n", srv->player[i].fire);
			}
		}
	}
}
