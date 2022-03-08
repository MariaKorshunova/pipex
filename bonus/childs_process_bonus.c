/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:54:27 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 21:13:14 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_child_first(t_pipex	*pipex, char **argv, char **envp)
{
	pipex->child = fork();
	if (pipex->child < 0)
		ft_error_fork(pipex);
	else if (pipex->child == 0)
	{
		ft_close_file(pipex->pipe1[0], NULL);
		ft_open_infile(pipex, argv);
		if (pipex->infile_fd == -1)
			ft_error_open_file(pipex, pipex->pipe1[1]);
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		{
			ft_close_file(pipex->infile_fd, argv[1]);
			ft_close_file(pipex->pipe1[1], NULL);
			ft_error_dup(pipex);
		}
		if (dup2(pipex->pipe1[1], STDOUT_FILENO) == -1)
		{
			ft_close_file(pipex->infile_fd, argv[1]);
			ft_close_file(pipex->pipe1[1], NULL);
			ft_error_dup(pipex);
		}
		ft_close_file(pipex->infile_fd, argv[1]);
		ft_close_file(pipex->pipe1[1], NULL);
		ft_exec(pipex, argv[2], envp);
	}
}

static void	ft_child_last(t_pipex *pipex, char **argv, char **envp, int *fd)
{
	pipex->child = fork();
	if (pipex->child < 0)
		ft_error_fork(pipex);
	else if (pipex->child == 0)
	{
		ft_close_file(fd[1], NULL);
		ft_open_outfile(pipex, argv);
		if (pipex->outfile_fd == -1)
			ft_error_open_file(pipex, fd[0]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			ft_close_file(pipex->outfile_fd, argv[4]);
			ft_close_file(fd[0], NULL);
			ft_error_dup(pipex);
		}
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		{
			ft_close_file(pipex->outfile_fd, argv[4]);
			ft_close_file(fd[0], NULL);
			ft_error_dup(pipex);
		}
		ft_close_file(pipex->outfile_fd, argv[4]);
		ft_close_file(fd[0], NULL);
		ft_exec(pipex, argv[pipex->argc - 2], envp);
	}
}

void	ft_child(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 0;
	ft_child_first(pipex, argv, envp);
	ft_child_last(pipex, argv, envp, (int *)pipex->pipe1);
}
