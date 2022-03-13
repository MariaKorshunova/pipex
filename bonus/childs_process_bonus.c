/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:54:27 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/13 15:29:55 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_define_count(t_pipex *pipex, int *middle_cmd, int *start)
{
	if (pipex->heredoc == 1)
	{
		*middle_cmd = pipex->argc - 6;
		*start = 4;
	}
	else
	{
		*middle_cmd = pipex->argc - 5;
		*start = 3;
	}
}

void	ft_child_first(t_pipex	*pipex, char **argv, char **envp)
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

void	ft_manage_middle_child(t_pipex *pipex, char **argv, int *i)
{
	int	middle_cmd;
	int	start_middle_cmd;

	ft_define_count(pipex, &middle_cmd, &start_middle_cmd);
	while (*i < middle_cmd)
	{
		if (*i % 2 == 0)
		{
			if (pipe(pipex->pipe2) == -1)
				ft_error_pipe(pipex, 1);
			ft_child_middle(pipex, argv[start_middle_cmd + *i],
				pipex->pipe1, pipex->pipe2);
			ft_close_file(pipex->pipe1[1], NULL);
		}
		else
		{
			if (pipe(pipex->pipe1) == -1)
				ft_error_pipe(pipex, 2);
			ft_child_middle(pipex, argv[start_middle_cmd + *i],
				pipex->pipe2, pipex->pipe1);
			ft_close_file(pipex->pipe2[0], NULL);
			ft_close_file(pipex->pipe2[1], NULL);
		}
		(*i)++;
	}	
}

void	ft_child_middle(t_pipex *pipex, char *n_argv, int *fd1, int *fd2)
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

void	ft_child_last(t_pipex *pipex, char **argv, int *fd)
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
			ft_close_file(pipex->outfile_fd, argv[pipex->argc - 1]);
			ft_close_file(fd[0], NULL);
			ft_error_dup(pipex);
		}
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		{
			ft_close_file(pipex->outfile_fd, argv[pipex->argc - 1]);
			ft_close_file(fd[0], NULL);
			ft_error_dup(pipex);
		}
		ft_close_file(pipex->outfile_fd, argv[pipex->argc - 1]);
		ft_close_file(fd[0], NULL);
		ft_exec(pipex, argv[pipex->argc - 2], pipex->envp);
	}
}
