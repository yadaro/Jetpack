/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Net
*/

#include <netdb.h>
#include <stddef.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "network.h"
#include "client.h"
#include "map.h"
#include "print.h"
#include "parse_net.h"

static int			create_socket(void)
{
	protoent_t		pe = getprotobyname("TCP");
	int			sock = 0;

	if (pe == NULL)
		return (print_error("TCP Protocol not avaible."));
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (sock <= 0)
		return (print_error("Can't create a socket."));
	return (sock);
}

void				close_socket(int i)
{
	if (close(i) == -1)
		exit(print_exit("Can't close the socket."));
	printf("[Info] Socket is now closed.\n");
}

int				init_network(connection_t *co)
{
	co->socket = create_socket();
	if (co->socket == -1)
		return (-1);
	if (strcmp(co->ip, "localhost") == 0)
		co->ip = "127.0.0.1";
	co->s_in.sin_family = AF_INET;
	co->s_in.sin_port = htons(co->port);
	co->s_in.sin_addr.s_addr = inet_addr(co->ip);
	printf("[Info] Trying to connect to %s : %i.\n", co->ip, co->port);
	if (connect(co->socket, (const struct sockaddr *) &co->s_in,
			sizeof(co->s_in)) < 0)
		return (print_error("Can't connect to the server"));
	else
		printf("[Info] Connected to %s:%i.\n", co->ip, co->port);
	return (0);
}

bool				protocol_to_start(client_t *c)
{
	char			buff[BUFF_SIZE];

	if (!c->connected)
		return (false);
	dprintf(c->co.socket, "ID\n");
	if (recv(c->co.socket, buff, BUFF_SIZE, 0) < 0)
		return (false);
	if (strncmp("ID", buff, 2) == 0)
		c->game.player.id = (unsigned int)atoi(&buff[2]);
	if (!c->game.player.id)
		return (false);
	memset(buff, 0, sizeof(buff));
	dprintf(c->co.socket, "MAP\n");
	if (recv(c->co.socket, buff, BUFF_SIZE, 0) < 0)
		return (false);
	if (strncmp("MAP", buff, 3) == 0)
		parse_map(c, &buff[3]);
	dprintf(c->co.socket, "READY\n");
	memset(buff, 0, sizeof(buff));
	printf("Ready, Waiting to receive START message.\n");
	if (recv(c->co.socket, buff, BUFF_SIZE, 0) < 0)
		return (false);
	if (strncmp("START", buff, 5) == 0)
		c->game.run = true;
	return (true);
}

void *network_update_loop(void *client)
{
	client_t *c = client;
	char buff[BUFF_SIZE];
	const char s[2] = "\n";

	while (c->game.run) {
		memset(buff, 0, sizeof(buff));
		if (recv(c->co.socket, buff, BUFF_SIZE, 0) < 0) {
			print_exit("Error with recv\n");
			return ((void *) 84);
		}
		char *token = strtok(buff, s);
		while ((token != NULL) && (c->game.run)) {
			if (strncmp("PLAYER", token, 6) == 0)
				parse_player(client, token);
			else if (strncmp("COIN", token, 4) == 0)
				parse_coin(client, token);
			else if (strncmp("FINISH", token, 6) == 0)
				parse_finish(client, token);
			token = strtok(NULL, s);
		}
		usleep((1000 / 250) * 1000);
	}
	return ((void *) 0);
}
