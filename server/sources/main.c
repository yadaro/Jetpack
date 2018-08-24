/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** main.c
*/

#include <stdlib.h>
#include "network.h"
#include "server.h"
#include "tools.h"
#include "print.h"
#include "error.h"

static void		init_co(server_t *srv)
{
	srv->co.max_socket = 0;
	srv->co.master_socket = 0;
	for (int i = 0; i < MAX_CLIENTS; i++)
		srv->co.clients_sockets[i] = 0;
	srv->co.port = 0;
	srv->co.ready = false;
	srv->start = false;
}

static void		init_player(server_t *srv)
{
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		srv->player[i].id = 0;
		srv->player[i].score = 0;
		srv->player[i].fire = false;
		srv->player[i].req_map = false;
		srv->player[i].req_id = false;
		srv->player[i].ready = false;
		srv->player[i].x = 0;
		srv->player[i].y = srv->map.y / 2;
		srv->player[i].dead = false;
	}
}

int			main(int ac, char **av)
{
	server_t	*srv;

	if (!(srv = malloc(sizeof(server_t))))
		return (print_exit(ERR_MALLOC));
	if (!check_flags(ac, av))
		return (print_exit(BAD_ARG));
	init_co(srv);
	if (parse_flags(ac, av, srv) != 0)
		return (84);
	init_player(srv);
	setup_connection(&srv->co);
	clients_connection(srv);
	return (0);
}
