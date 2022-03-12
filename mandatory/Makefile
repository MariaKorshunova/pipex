# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:08:19 by jmabel            #+#    #+#              #
#    Updated: 2022/03/12 09:51:43 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=  ../pipex

HEADER		=  pipex.h

CC 			= 	cc
CFLAGS		=  -Wall -Wextra -Werror

SRCS 		=	pipex.c			parser.c			childs_process.c\
				free.c			file_operations.c	ft_exec.c\
				libft_utils.c	ft_split.c			error.c

OBJ			=  $(SRCS:.c=.o)

all			:  $(NAME)

$(NAME)		:  $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o	:  %.c $(HEADER)
	$(CC) $(CFLAGS)  -c  $<  -o $@

.PHONY		:  all clean fclean re

clean		:
	$(RM) $(OBJ)

fclean		: clean
	$(RM) $(NAME)

re			:  fclean all