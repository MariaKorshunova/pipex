# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:08:19 by jmabel            #+#    #+#              #
#    Updated: 2022/03/06 17:18:53 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	pipex_bonus

HEADER				=	pipex_bonus.h

SRCS				=	pipex_bonus.c	free_bonus.c\

OBJ 				= 	$(SRCS:%.c=%.o)

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror

RM 					= 	rm -rf

all					:	$(NAME)
	mv pipex_bonus pipex
	mv pipex ../

$(NAME)				:	$(OBJ)

%.o					: %.c $(HEADER)
	$(CC) $(CFLAGS)  -c  $<  -o $@
	
.PHONY				:	all clean fclean re

clean:
	$(RM) $(OBJ)

fclean				: clean
	$(RM) ../$(NAME)

re					: fclean all