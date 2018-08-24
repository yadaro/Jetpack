##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Basic Makefile
##

#Project Settings
NAME		= serverJ2T3
DEBUG		= no

PATH_SOURCES	= ./sources
PATH_INCLUDE	= ./includes
LIBS		=
LDFLAGS		=

#Sources
SRCS		= ${PATH_SOURCES}/main.c		\
		${PATH_SOURCES}/tools.c			\
		${PATH_SOURCES}/print.c			\
		${PATH_SOURCES}/map.c			\
		${PATH_SOURCES}/network.c		\
		${PATH_SOURCES}/get_line.c		\
		${PATH_SOURCES}/init_wordtab.c		\
		${PATH_SOURCES}/str_to_wordtab.c	\
		${PATH_SOURCES}/cmd.c			\
		${PATH_SOURCES}/game.c			\
		${PATH_SOURCES}/timer.c			\
		${PATH_SOURCES}/init_game.c

OBJS		= $(SRCS:.c=.o)

#Compiler Choice
detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(DEBUG), yes)
	CC	= clang
else
	ifeq ($(detected_OS), Darwin)
		CC	= gcc-8
	else
		CC	= gcc
	endif
endif

#Compilation flags
ifeq ($(DEBUG), yes)
	CFLAGS	= -Weverything
else
	CFLAGS	= -Wall -Wextra -Wall -ansi -pedantic
endif
CFLAGS		+= -std=c11 -O2 -fPIC

#Output Functions / Colors Setting
RED		= "\033[1;31m"
NC		= "\033[0m"

aff_comp        = echo "Creating .o file with" $(CC) "from" $<
aff_error       = echo $(RED) "\n |-----\n | Error while creating .o file with" $(CC) "from" $< "\n |-----\n" $(NC)

#Target Rules
all:		$(NAME)

# docker-compile :
# 		docker build -t JetpackServer .

$(NAME):	$(OBJS)
		@$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

%.o: %.c
		@($(CC) -o $@ -c $< $(CFLAGS) -I${PATH_INCLUDE} && $(aff_comp)) || $(aff_error)

clean:
		@$(RM) $(OBJS)

fclean: 	clean
		@$(RM) $(NAME)

re: 		fclean all

.PHONY: all serverJ2T3 clean fclean re docker-compile
