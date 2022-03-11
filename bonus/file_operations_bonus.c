/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:54:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/11 21:41:05 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open_infile(t_pipex *pipex, char **argv)
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
		ft_error(argv[1], strerror(errno));
}

void	ft_open_outfile(t_pipex *pipex, char **argv)
{
	pipex->outfile_fd = open(argv[pipex->argc - 1],
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
		ft_error(argv[pipex->argc - 1], strerror(errno));
}

void	ft_close_file(int fd, char *name)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			ft_error(name, strerror(errno));
	}
}

void	ft_close_last_pipe(t_pipex *pipex, int i)
{
	if (i % 2 == 0)
	{
		ft_close_file(pipex->pipe1[0], NULL);
		ft_close_file(pipex->pipe1[1], NULL);
	}
	else
	{
		ft_close_file(pipex->pipe2[0], NULL);
		ft_close_file(pipex->pipe2[1], NULL);
	}
}
