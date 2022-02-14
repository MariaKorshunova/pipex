/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/14 19:23:27 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid1;

	if (argc != 5)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		ft_putendl_fd("Error with opening the pipe", 2);
		return (2);
	}
	pid1 = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Error with fork", 2);
		return (3);
	}
	else if (pid1 == 0)
	{
		//child process
	}
	return (0);
}
