##
## EPITECH PROJECT, 2020
## PSU_minishell1_2019
## File description:
## Makefile
##

SRC	=	src/main.c			\
		src/my_str_to_word_array.c	\
		src/my_strlen.c			\
		src/my_int_to_str.c		\
		src/my_revstr.c			\
		src/minishell.c			\
		src/get_next_line.c		\
		src/get_env.c			\
		src/path_to_word_array.c	\
		src/check_perm.c		\
		src/env_exec.c			\
		src/my_strcmp.c			\
		src/execute.c			\
		src/my_isnum.c			\
		src/my_getnbr.c			\
		src/check_orders.c		\
		src/my_strncmp.c		\
		src/setenv_unsetenv.c		\
		src/my_strcpy.c			\
		src/my_unsetenv.c		\
		src/free_tab.c			\
		src/copy_envp.c			\
		src/env_name.c			\
		src/cd.c			\
		src/print_error.c		\
		src/setenv_condition.c		\
		src/parse_command.c		\
		src/exec_order.c		\
		src/shell.c			\
		src/redirections.c		\
		src/parse_command_bis.c		\

NAME	=	mysh

CPPFLAGS=	$(INCLUDE)

CFLAGS	=	-Wall -Wextra -g3

OBJ	=	$(SRC:.c=.o)

INCLUDE	=	-I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
