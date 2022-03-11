/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:54:27 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/11 21:39:38 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_child_first(t_pipex	*pipex, char **argv, char **envp)
{
	pipex->child = fork();
	if (pipex->child < 0)
		ft_error_fork(pipex, pipex->pipe1, 0);
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

static void	ft_child_middle(t_pipex *pipex, char *n_argv, int *fd1, int *fd2)
{
	pipex->child = fork();
	if (pipex->child < 0)
		ft_error_fork(pipex, NULL, 1);
	else if (pipex->child == 0)
	{
		ft_close_file(fd1[1], NULL);
		ft_close_file(fd2[0], NULL);
		if (dup2(fd1[0], STDIN_FILENO) == -1)
		{
			ft_close_file(fd1[0], NULL);
			ft_close_file(fd2[1], NULL);
			ft_error_dup(pipex);
		}
		if (dup2(fd2[1], STDOUT_FILENO) == -1)
		{
			ft_close_file(fd1[0], NULL);
			ft_close_file(fd2[1], NULL);
			ft_error_dup(pipex);
		}
		ft_close_file(fd1[0], NULL);
		ft_close_file(fd2[1], NULL);
		ft_exec(pipex, n_argv, pipex->envp);
	}
}

static void	ft_child_last(t_pipex *pipex, char **argv, char **envp, int *fd)
{
	pipex->child = fork();
	if (pipex->child < 0)
		ft_error_fork(pipex, fd, 0);
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

static void	ft_manage_middle_child(t_pipex *pipex, char **argv, int *i)
{
	while (*i < pipex->argc - 5)
	{
		if (*i % 2 == 0)
		{
			if (pipe(pipex->pipe2) == -1)
				ft_error_pipe(pipex, 1);
			ft_child_middle(pipex, argv[3 + *i], pipex->pipe1, pipex->pipe2);
			ft_close_file(pipex->pipe1[0], NULL);
			ft_close_file(pipex->pipe1[1], NULL);
		}
		else
		{
			if (pipe(pipex->pipe1) == -1)
				ft_error_pipe(pipex, 2);
			ft_child_middle(pipex, argv[3 + *i], pipex->pipe2, pipex->pipe1);
			ft_close_file(pipex->pipe2[0], NULL);
			ft_close_file(pipex->pipe2[1], NULL);
		}
		(*i)++;
	}	
}

int	ft_child(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 0;
	ft_child_first(pipex, argv, envp);
	ft_manage_middle_child(pipex, argv, &i);
	if (i % 2 == 0)
		ft_child_last(pipex, argv, envp, pipex->pipe1);
	else
		ft_child_last(pipex, argv, envp, pipex->pipe2);
	return (i);
}
