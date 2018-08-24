/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** network
*/

#pragma once
#include "client.h"

void	close_socket(int fd);
int	init_network(connection_t *co);
bool	protocol_to_start(client_t *c);
void	*network_update_loop(void *client);
