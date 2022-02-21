/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:02:52 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/21 16:03:33 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_files(t_pipex *pipex, char **argv)
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[4], O_RDONLY);
	if (pipex->infile_fd == -1 || pipex->outfile_fd == -1)
	{
		if (pipex->infile_fd == -1 && pipex->outfile_fd != -1)
			close(pipex->outfile_fd);
		if (pipex->outfile_fd == -1 && pipex->infile_fd != -1)
			close(pipex->infile_fd);
		perror("");
		exit (ERR_FILE);
	}
}

void	ft_close_file(int fd)
{
	if (close(fd) == -1)
	{
		perror("");
		exit (ERR_FILE);
	}
}
