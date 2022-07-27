# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 16:09:57 by nadesjar          #+#    #+#              #
#    Updated: 2022/07/27 01:03:05 by nadesjar         ###   ########.fr        #
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
PATH_LIB	= ./src/lib/
PATH_CHECK	= ./src/check/
PATH_UTILS	= ./src/utils/

FILES 		= $(PATH_SRC)pipex.c \
			$(PATH_LIB)ft_split.c $(PATH_LIB)ft_strjoin.c $(PATH_LIB)ft_strnstr.c \
			$(PATH_LIB)ft_substr.c $(PATH_LIB)ft_strlen.c $(PATH_LIB)ft_strdup.c \
			$(PATH_LIB)free_ptr.c $(PATH_LIB)ft_strchr.c \
			$(PATH_CHECK)check.c \
			$(PATH_UTILS)utils.c \

OBJS 		= $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(FILES))

CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra

PRINTF		= make_lib
PRINTF_A	= ft_printf/libftprintf.a

NAME 		= pipex

REMOVE		= ./ft_printf/*.o \
			./ft_printf/*.a \
			./src/*.o pipex \

all: $(PRINTF) $(NAME)

$(NAME): $(OBJS)
	@echo $(LILAS)"COMPILATION DE PIPEX EN COURS..."$(RESET)
	cp $(PRINTF_A) $(NAME)
	gcc $(OBJS) $(CFLAGS) $(PRINTF_A) -o pipex
	@echo $(LILAS)"PIPEX READY !!!"$(RESET)
#./pipex infile.txt "grep do" "wc" outfile.txt

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)lib
	@mkdir -p $(PATH_OBJS)check
	@mkdir -p $(PATH_OBJS)utils
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