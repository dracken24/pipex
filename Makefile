# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 16:09:57 by nadesjar          #+#    #+#              #
#    Updated: 2022/07/19 13:52:41 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIGHT_RED	= $(shell tput -Txterm setaf 1)
LIGHT_GREEN	= $(shell tput -Txterm setaf 2)
LIGHT_BROWN	= $(shell tput -Txterm setaf 3)
CYAN		= $(shell tput -Txterm setaf 4)
LILAS		= $(shell tput -Txterm setaf 5)
LIGHT_CYAN	= $(shell tput -Txterm setaf 6)
WHITE		= $(shell tput -Txterm setaf 7)
RESET		= "\033[0m"

PATH_OBJS 	= ./objs/
PATH_SRC	= ./src/
PATH_lib	= ./src/lib/
PATH_check	= ./src/check/
PATH_GNL	= ./src/gnl/
PATH_B		= ./src/bonus/

FILES 		= $(PATH_SRC)pipex.c \
			$(PATH_lib)ft_split.c $(PATH_lib)ft_strjoin.c $(PATH_lib)ft_strnstr.c \
			$(PATH_lib)ft_substr.c $(PATH_lib)ft_strlen.c $(PATH_lib)ft_strdup.c \
			$(PATH_lib)free_ptr.c $(PATH_lib)ft_strchr.c \
			$(PATH_check)check.c \
			$(PATH_GNL)get_next_line.c $(PATH_GNL)get_next_line_utils.c \

OBJS 		= $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(FILES))

CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra

PRINTF		= make_lib
PRINTF_A	= ft_printf/libftprintf.a

NAME 		= pipex

REMOVE		= ./ft_printf/*.o \
			./ft_printf/*.a \
			./src/*.o pipex \

all: re $(PRINTF) $(NAME)

$(NAME): $(OBJS)
	@echo $(LILAS)"COMPILATION DE PIPEX EN COURS..."$(RESET)
	cp $(PRINTF_A) $(NAME)
	gcc $(OBJS) $(CFLAGS) $(PRINTF_A) -o pipex
	@echo $(LILAS)"PIPEX READY !!!"$(RESET)
	./pipex entry.txt "cat" "grep do" "wc" exit.txt
# cmd shell : cat entry.txt | grep do | wc >> exit.txt 

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)lib
	@mkdir -p $(PATH_OBJS)check
	@mkdir -p $(PATH_OBJS)gnl
	$(CC) $(CFLAGS) -c $< -o $@

make_lib:
	$(MAKE) -C ./ft_printf

push:
	@(git add .)
	@(git commit -m "nadesjar42")
	@(git push)

clean:
	@rm -f $(OBJ) $(REMOVE)
	@rm -fr ./objs
	@echo $(LIGHT_GREEN)"BYE BYE"$(RESET)

fclean: clean
	@rm -f $(NAME) $(LIBFT_A)
	
re:	fclean all

.PHONY: all make_lib push clean fclean re