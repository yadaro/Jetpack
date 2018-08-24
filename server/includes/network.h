/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Network
*/

#pragma once
#include <stdnoreturn.h>
#include "server.h"

typedef struct	sockaddr *sockaddr_t;
typedef struct	protoent *protoent_t;

void		setup_connection(connection_t *co);
noreturn void		clients_connection(server_t *srv);
void		close_socket(int i);
char            *get_line(int fd);
void		accept_new_client(server_t *s);
void		init_fd_set(server_t *s);
