/*
** EPITECH PROJECT, 2018
** Jetpack
** File description:
** Network
*/

#include <sys/time.h>
#include <stdbool.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <printf.h>
#include <arpa/inet.h>
#include <memory.h>
#include <stdio.h>
#include <stdnoreturn.h>
#include "server.h"
#include "network.h"
#include "print.h"

static int		create_socket(void)
{
	protoent_t	pe = getprotobyname("TCP");
	int		opt = 1;
	int		sock = 0;

	if (pe == NULL)
		return (print_error("TCP Protocol not avaible."));
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (sock <= 0)
		return (print_error("Can't create a socket."));
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
		sizeof(opt)) < 0)
		return (print_error("Can't set Sock Opt."));
	return (sock);
}

void			close_socket(int i)
{
	if (close(i) == -1)
		exit(print_exit("Can't close the socket."));
	printf("[Info] Socket fd %i is now closed.\n", i);
}

void			setup_connection(connection_t *co)
{
	co->master_socket = create_socket();
	if (co->master_socket == -1)
		exit(84);
	co->s_in.sin_family = AF_INET;
	co->s_in.sin_port = htons(co->port);
	co->s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(co->master_socket, (const sockaddr_t) &co->s_in,
		sizeof(co->s_in)) < 0) {
		close_socket(co->master_socket);
		exit(print_exit("Can't bind socket."));
	}
	if (listen(co->master_socket, MAX_LISTEN) < 0) {
		close_socket(co->master_socket);
		exit(print_exit("Can't create a queue."));
	}
	for (int i = 0; i < MAX_CLIENTS; i++)
		co->clients_sockets[i] = 0;
	printf("[Info] Server Started on port %d\n", co->port);
	co->ready = true;
}

void		init_fd_set(server_t *s)
{
	FD_ZERO(&s->co.fds);
	FD_SET(s->co.master_socket, &s->co.fds);
	s->co.max_socket = s->co.master_socket;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (s->co.clients_sockets[i] > 0)
			FD_SET(s->co.clients_sockets[i], &s->co.fds);
		if (s->co.clients_sockets[i] > s->co.max_socket)
			s->co.max_socket = s->co.clients_sockets[i];
	}
}

void		accept_new_client(server_t *s)
{
	int		new_socket = 0;
	int		addrlen = sizeof(s->co.s_in);

	if (FD_ISSET(s->co.master_socket, &s->co.fds)) {
		if ((new_socket = accept(s->co.master_socket,
					(const sockaddr_t)&s->co.s_in,
					(socklen_t *)&addrlen)) < 0)
			exit(print_exit("Accept error."));
		printf("[Info] New client on socket fd %d.\n", new_socket);
		for (int i = 0; i < MAX_CLIENTS; i++)
			if (s->co.clients_sockets[i] == 0) {
				s->co.clients_sockets[i] = new_socket;
				printf("[Info] Added client to the list of clients as %d.\n", i);
				break;
			}
	}
}
