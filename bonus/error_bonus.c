/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:56:35 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 19:48:12 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *name, char *str_error)
{
	ft_putstr_fd("./pipex: ", 2);
	ft_putstr_fd(str_error, 2);
	if (name)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	ft_error_dup(t_pipex *pipex)
{
	ft_free_array(pipex->bin_path);
	perror("./pipex");
	exit(ERR_DUP);
}

void	ft_error_open_file(t_pipex *pipex, int fd)
{
	ft_free_array(pipex->bin_path);
	ft_close_file(fd, NULL);
	exit (ERR_FILE);
}

void	ft_error_fork(t_pipex *pipex)
{
	ft_close_file(pipex->fd[0], NULL);
	ft_close_file(pipex->fd[1], NULL);
	ft_free_array(pipex->bin_path);
	perror ("./pipex: ");
	exit (ERR_FORK);
}
