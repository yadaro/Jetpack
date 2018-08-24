/*
** EPITECH PROJECT, 2018
** jetpack
** File description:
** server
*/

#pragma once
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define DISPLAY_BEGUG == false
#define MAX_LISTEN 4
#define MAX_CLIENTS 2
#define SIZE_CMD 3

typedef struct			s_wd {
	char			**tab;
	int			i;
	int			x;
	int			y;
	char			pad[4];
}				t_wd;

typedef struct			connection_s {
	fd_set			fds;
	struct sockaddr_in	s_in;
	int			max_socket;
	int			master_socket;
	int	 		clients_sockets[MAX_CLIENTS];
	unsigned short		port;
	bool			ready;
	char			pad_1[5];
}				connection_t;

typedef struct			map_s {
	unsigned long		x;
	unsigned long		y;
	char			**map;
}				map_t;

typedef struct			player_s {
	double			x;
	double			y;
	int			id;
	int			score;
	bool			fire;
	bool			req_map;
	bool			req_id;
	bool			ready;
	bool			dead;
	char			pad_2[3];
}				player_t;

typedef struct			server_s {
	connection_t		co;
	player_t		player[MAX_CLIENTS];
	map_t			map;
	char			pad_3[4];
	int			gravity;
	bool			start;
	bool			end;
	char			pad_4[6];
}				server_t;

typedef struct	ptr_f_cmd_s {
	char	name[256];
	void	(*func)(server_t *, int);
}	ptr_f_cmd_t;

void	init_wd(t_wd *vr);
bool	get_map(char *map_path, server_t *srv);
char	*get_line(int fd);
char	**str_to_wordtab(char *s, char param);
void	print_map(server_t *, int );
void	set_id(server_t *, int );
void	set_ready(server_t *, int );
void	loop_game(server_t *srv, int , char *);
void	set_delay(int ms);

static const ptr_f_cmd_t cmd[SIZE_CMD] = {
	{"map", print_map},
	{"id", set_id},
	{"ready", set_ready},
};
