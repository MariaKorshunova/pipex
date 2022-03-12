# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 15:28:13 by jmabel            #+#    #+#              #
#    Updated: 2022/03/12 09:54:03 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all		:
	make -C ./mandatory

bonus	:
	make -C ./bonus

.PHONY	:	all clean fclean re bonus

clean	:
	make clean -C ./mandatory
	make clean -C ./bonus

fclean	: clean
	make fclean -C ./mandatory
	make fclean -C ./bonus

re		: fclean all
rebonus : fclean bonus