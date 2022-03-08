# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:08:19 by jmabel            #+#    #+#              #
#    Updated: 2022/03/08 18:56:54 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	pipex_bonus

HEADER				=	pipex_bonus.h

SRCS				=	pipex_bonus.c				parser_bonus.c\
						childs_process_bonus.c		free_bonus.c\
						file_operations_bonus.c		ft_exec_bonus.c\
						libft_utils_bonus.c			ft_split_bonus.c\
						error_bonus.c

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