# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 12:00:19 by nadesjar          #+#    #+#              #
#    Updated: 2022/04/28 15:04:26 by nadesjar         ###   ########.fr        #
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

SRCS 		= ft_hexa.c ft_printf.c ft_put.c ft_itoa.c\

OBJ 		= $(SRCS:%c=%o)

CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra

AR 			= ar -rcs
NAME 		= libftprintf.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	echo $(PURPLE)"COMPILE MOI CE PRINTF LA..."$(RESET)
	$(AR) $(NAME) $(OBJ)
	echo $(PURPLE)"MALADE CA A COMPILER !!!"$(RESET)

push:
	@(git add .)
	@(git commit -m "nadesjar42")
	@(git push)

clean:
	@rm -f $(OBJ) ./libft/*.o
	@echo $(PURPLE)"BYE BYE"$(RESET)
	

fclean: clean
	@rm -f $(NAME) $(LIBFT_A) a.out gcc
	
re:	fclean all

.PHONY: all make_lib push clean fclean re
