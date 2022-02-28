/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:02:52 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/28 19:44:17 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_files(t_pipex *pipex, char **argv)
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		ft_error(argv[1]);
	}
	pipex->outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		if (pipex->infile_fd != -1)
			ft_close_file(pipex->infile_fd, argv[1]);
		ft_error(argv[4]);
	}
	if (pipex->infile_fd == -1 || pipex->outfile_fd == -1)
		exit(ERR_FILE);
}

void	ft_close_file(int fd, char *name)
{
	if (close(fd) == -1)
	{
		ft_error(name);
		exit(ERR_FILE);
	}
}
