# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:08:19 by jmabel            #+#    #+#              #
#    Updated: 2022/03/06 16:33:28 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	pipex

HEADER				=	pipex.h

SRCS				=	pipex.c	parser.c	childs_process.c	free.c\
						file_operations.c	ft_exec.c			libft_utils.c\
						ft_split.c

OBJ 				= 	$(SRCS:%.c=%.o)

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror

RM 					= 	rm -rf

all					:	$(NAME)
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