##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Basic Makefile
##

#Project Settings
# MY_MAKE		= $(MAKE)
MY_MAKE		= make
RM		= rm -f

NAME_CLIENT	= clientJ2T3
NAME_SERVER	= serverJ2T3
PATH_CLIENT	= ./client/
PATH_SERVER	= ./server/

#Output Functions / Colors Setting
BLUE		= "\033[1;36m"
GREEN		= "\033[1;32m"
YELLOW		= "\033[1;33m"
NC		= "\033[0m"

aff_make_client	= echo "\n"$(GREEN) "** Make Client DONE **" $(NC) "\n\t-Compiled file: " $(NAME_CLIENT) "\n\n"
aff_make_server	= echo "\n"$(GREEN) "** Make Server DONE **" $(NC) "\n\t-Compiled file: " $(NAME_SERVER) "\n"
aff_clean	= echo $(YELLOW) "** Clean DONE **" $(NC) "\n\t-Cleaned .o files\n"
aff_fclean	= echo $(BLUE) "** Fclean DONE **" $(NC) "\n"

#Target Rules
all:		$(NAME_CLIENT) $(NAME_SERVER)

# docker-compile :
# 		docker build -t irc-server .

$(NAME_CLIENT):
		@$(MY_MAKE) -C $(PATH_CLIENT) && cp $(PATH_CLIENT)$(NAME_CLIENT) $(NAME_CLIENT)
		@$(aff_make_client)

$(NAME_SERVER):
		@$(MY_MAKE) -C $(PATH_SERVER) && cp $(PATH_SERVER)$(NAME_SERVER) $(NAME_SERVER)
		@$(aff_make_server)

client:
		@$(MY_MAKE) -C $(PATH_CLIENT) && cp $(PATH_CLIENT)$(NAME_CLIENT) $(NAME_CLIENT)
		@$(aff_make_client)

moulilol:
		@$(MY_MAKE) -C $(PATH_CLIENT) moulilol && cp $(PATH_CLIENT)$(NAME_CLIENT) $(NAME_CLIENT)
		@$(aff_make_client)

server:
		@$(MY_MAKE) -C $(PATH_SERVER) && cp $(PATH_SERVER)$(NAME_SERVER) $(NAME_SERVER)
		@$(aff_make_server)

clean:
		@$(MY_MAKE) -C $(PATH_CLIENT) clean
		@$(MY_MAKE) -C $(PATH_SERVER) clean
		@$(aff_clean)

fclean:
		@$(MY_MAKE) -C $(PATH_CLIENT) fclean
		@$(MY_MAKE) -C $(PATH_SERVER) fclean
		@$(RM) $(NAME_CLIENT) $(NAME_SERVER)
		@$(aff_clean)
		@$(aff_fclean)

re: 		fclean all

.PHONY: all clean fclean re client server moulilol clientJ2T3 serverJ2T3 docker-compile
