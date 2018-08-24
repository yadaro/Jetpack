/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** timer.c
*/

#include <stdio.h>
#include <time.h>
#include "server.h"

void set_delay(int ms)
{
	int ms_since = 0;
	int end = 0;

	if (ms <= 0) {
		printf("parameter need to be above 0\n");
		return ;
	}
	ms_since = clock() * 1000 / CLOCKS_PER_SEC;
	end = ms_since + ms;
	while (ms_since <= end)
		ms_since = clock() * 1000 / CLOCKS_PER_SEC;
}
