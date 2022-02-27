# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:08:19 by jmabel            #+#    #+#              #
#    Updated: 2022/02/27 18:39:12 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	pipex

HEADER				=	pipex.h

SRCS				=	pipex.c	parser.c	childs_process.c	free.c\
						file_operations.c\
						libft_utils.c	ft_split.c\

OBJ 				= 	$(SRCS:%.c=%.o)

CC 					= 	cc 
CFLAGS 				= 	#-Wall -Wextra #-Werror

RM 					= 	rm -rf

all					:	$(NAME) 

$(NAME)				:	$(OBJ)

%.o					: %.c $(HEADER)
	$(CC) $(CFLAGS)  -c  $<  -o $@ 

.PHONY				:	all clean fclean re bonus

clean:
	$(RM) $(OBJ) 

fclean				: clean
	$(RM) $(NAME)

re					: fclean all