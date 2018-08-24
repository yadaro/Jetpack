/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** init_game.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
#include "server.h"
#include "network.h"
#include "print.h"

static void	do_cmd(server_t *srv, char *line, int fd)
{
	int	c = 0;
	int	j = 0;

	for (int f = 0; line[f]; ++f) {
		if (line[f] >= 65 && line[f] <= 90)
			line[f] += 32;
	}
	for (int i = 0 ; i < SIZE_CMD; ++i)
		if (!strcmp(cmd[i].name, line))
			cmd[i].func(srv, fd);
	for (int c = 0 ; c < MAX_CLIENTS; ++c)
		if (srv->player[c].ready == true)
			++j;
	if (j == MAX_CLIENTS) {
		if (srv->start != true) {
			for (int i = 0 ; i < MAX_CLIENTS; ++i)
				dprintf(srv->player[i].id, "START\n");
			loop_game(srv, fd, line);
		}
	}
}

static void		reset_player(server_t *srv, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (fd == srv->player[i].id) {
			srv->player[i].id = 0;
			srv->player[i].score = 0;
			srv->player[i].fire = false;
			srv->player[i].req_map = false;
			srv->player[i].req_id = false;
			srv->player[i].ready = false;
			srv->player[i].x = 0;
			srv->player[i].y = 0;
			srv->player[i].dead = false;
		}
	}
}

static void		remove_client(server_t * srv, int fd)
{
	printf("[Info] Client %d disconnected.\n", fd);
	reset_player(srv, fd);
	close_socket(fd);
        fd = 0;
}

static void		check_client_input(server_t *s)
{
	char	*line;
	bool	isletter = false;

	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (FD_ISSET(s->co.clients_sockets[i], &s->co.fds)) {
			line = get_line(s->co.clients_sockets[i]);
			if (line != NULL)
				for (int j = 0; line[j]; j++)
					if (isalpha(line[j]))
						isletter = true;
			if (line == NULL)
				remove_client(s, s->co.clients_sockets[i]);
			else if (isletter) {
				printf("[Info] Message from fd %i : %s\n",
				s->co.clients_sockets[i], line);
				do_cmd(s, line, s->co.clients_sockets[i]);
			}
		}
	}
}

noreturn void			clients_connection(server_t *s)
{
	struct timeval	timeout;

	while (true) {
		init_fd_set(s);
		timeout.tv_sec = 50 / 1000;
		timeout.tv_usec = (50 % 1000) * 1000;
		if ((select(s->co.max_socket + 1, &s->co.fds, NULL, NULL,
			&timeout)) < 0)
			exit(print_exit("Select error."));
		accept_new_client(s);
		check_client_input(s);
	}
}
