/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Tools
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "error.h"
#include "server.h"
#include "tools.h"
#include "print.h"

bool		check_flags(int ac, char **av)
{
	int	f = 0;

	for (int i = 0; i != ac; ++i) {
		if (!strcmp(av[i], "-g") || !strcmp(av[i], "-p") ||
		!strcmp(av[i], "-m"))
			f++;
	}
	if (f != 3)
		return (false);
	return (true);
}

int		parse_flags(int ac, char **av, server_t *srv)
{
	for (int opt = 0; (opt = getopt(ac, av, "m:p:g:")) != -1;) {
		switch (opt) {
		case 'p' :
			if ((atoi(optarg) > 65534) || (atoi(optarg) <= 0))
				return (print_error(BAD_ARG));
			srv->co.port = (unsigned short) atoi(optarg);
			break;
		case 'g':
			if (!atoi(optarg))
				return (print_error(BAD_ARG));
			srv->gravity = atoi(optarg);
			break;
		case 'm':
			if (!get_map(optarg, srv))
				return (print_error(BAD_MAP));
			break;
		}
	}
	return (0);
}
