/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Tools
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "tools.h"
#include "client.h"
#include "error.h"
#include "print.h"

bool		check_flags(int ac, char **av)
{
	int	f = 0;

	for (int i = 0; i != ac; ++i) {
		if (!strcmp(av[i], "-h") || !strcmp(av[i], "-p"))
			f++;
	}
	if (f != 2)
		return (false);
	return (true);
}

int		parse_flags(int ac, char **av, connection_t *connect)
{
	for (int opt = 0; (opt = getopt(ac, av, "p:h:")) != -1;) {
		switch (opt) {
		case 'p' :
			if ((atoi(optarg) > 65534) || (atoi(optarg) <= 0))
				return (print_error(BAD_ARG));
			connect->port = 0;
			connect->port = (unsigned short)atoi(optarg);
			break;
		case 'h':
			connect->ip = optarg;
			break;
		}
	}
	return (1);
}
