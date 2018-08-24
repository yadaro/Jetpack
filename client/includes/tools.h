/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Tools
*/

#pragma once
#include <stdbool.h>
#include "client.h"

bool	check_flags(int ac, char **av);
int	parse_flags(int ac, char **av, connection_t *);
