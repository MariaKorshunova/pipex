# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:08:19 by jmabel            #+#    #+#              #
#    Updated: 2022/02/14 17:11:06 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	pipex

HEADER				=	pipex.h

SRCS				=	pipex.c\

LIBFT				=	./libft/libft.a

OBJ 				= 	$(SRCS:%.c=%.o)

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror

RM 					= 	rm -rf

all					:	$(NAME) 

$(NAME)				:	$(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L ./libft -lft -o $(NAME)

$(LIBFT)			:
	make -C ./libft

%.o					: %.c $(HEADER)
	$(CC) $(CFLAGS)  -c  $<  -o $@ 

.PHONY				:	all clean fclean re bonus

clean:
	$(RM) $(OBJ) 
	make clean -C ./libft

fclean				: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re					: fclean all