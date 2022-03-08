/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:31:20 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/07 12:52:28 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open_files(t_pipex *pipex, char **argv)
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
		ft_error(argv[1], strerror(errno));
	pipex->outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
		ft_error(argv[4], strerror(errno));
}

void	ft_close_file(int fd, char *name)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			ft_error(name, strerror(errno));
	}
}