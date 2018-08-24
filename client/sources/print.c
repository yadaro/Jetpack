/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Print Functions
*/

#include <stdio.h>
#include "print.h"

int		print_error(char *str)
{
	dprintf(2, "%s\n", str);
	return (-1);
}

int		print_exit(char *str)
{
	dprintf(2, "%s\n", str);
	return (84);
}
