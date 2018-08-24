/*
** EPITECH PROJECT, 2018
** Jetpack2Tek3
** File description:
** Client Main
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "init.h"
#include "network.h"
#include "tools.h"
#include "print.h"
#include "error.h"
#include "csfml.h"

static int		run(client_t *client)
{
	void		*ret = NULL;

	if (pthread_create(&client->thread, NULL, network_update_loop, client))
		return (print_exit("Can't create a thread."));
	printf("Starting the game.\n");
	csfml_game_loop(client);
	pthread_join(client->thread, &ret);
	if ((int)(intptr_t) ret == 84)
		return (84);
	csfml_free(client);
	return (0);
}

int			main(int ac, char **av)
{
	client_t	*client;

	if (!(client = malloc(sizeof(client_t))))
		return (print_exit(ERR_MALLOC));
	if (!check_flags(ac, av))
		return (print_exit(BAD_ARG));
	if (!parse_flags(ac, av, &client->co))
		return (84);
	if (!init_graph(client))
		return (84);
	if (!init(client))
		return (84);
	if (client->game.run)
		if (run(client) == 84)
			return (84);
	close_socket(client->co.socket);
	return (0);
}
