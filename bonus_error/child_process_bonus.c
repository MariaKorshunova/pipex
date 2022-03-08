/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:09:38 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 17:20:34 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_error_open_file(t_pipex *pipex, int fd)
{
	ft_free_array(pipex->bin_path);
	ft_close_file(fd, NULL);
	exit (ERR_FILE);
}

void	ft_child_first(t_pipex *pipex, char **argv, char **envp)
{
	pipex->child = fork();
	if (pipex->child < 0)
	{
		perror("./pipex: ");
		free(pipex->bin_path);
		exit(ERR_FORK);
	}
	else if (pipex->child == 0)
	{
		ft_close_file(pipex->outfile_fd, argv[pipex->argc - 1]);
		ft_close_file(pipex->pipe_fd1[0], NULL);
		if (pipex->infile_fd == -1)
			ft_error_open_file(pipex, pipex->pipe_fd1[1]);
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		{
			ft_close_file(pipex->infile_fd, argv[1]);
			ft_close_file(pipex->pipe_fd1[0], NULL);
			ft_error_dup(pipex);
		}
		if (dup2(pipex->pipe_fd1[1], STDOUT_FILENO) == -1)
		{
			ft_close_file(pipex->infile_fd, argv[1]);
			ft_close_file(pipex->pipe_fd1[1], NULL);
			ft_error_dup(pipex);
		}
		ft_close_file(pipex->infile_fd, argv[1]);
		ft_close_file(pipex->pipe_fd1[1], NULL);
		ft_exec(pipex, argv[2], envp);
		pipex->cmd = ft_get_cmd(argv[2]);
		if (!pipex->cmd)
		{
			ft_free_array(pipex->bin_path);
			perror("./pipex");
			exit (ERR_MEMORY_ALLOCATE);
		}
		ft_exec_without_path(pipex, envp, pipex->cmd);
		ft_exec_with_path(pipex, envp, pipex->cmd);
		ft_error(pipex->cmd[0], "Command not found");
		ft_free_pipex(pipex);
		exit(ERR_EXECUTE_CMD);
	}
}

void	ft_child_last(t_pipex *pipex, int *pipe_fd, char **argv, char **envp)
{
	pipex->child = fork();
	if (pipex->child < 0)
	{
		perror("./pipex: ");
		free(pipex->bin_path);
		exit(ERR_FORK);
	}
	else if (pipex->child == 0)
	{
		ft_close_file(pipex->infile_fd, argv[1]);
		ft_close_file(pipe_fd[1], NULL);
		if (pipex->outfile_fd == -1)
			ft_error_open_file(pipex, pipe_fd[0]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			ft_close_file(pipex->outfile_fd, argv[pipex->argc - 1]);
			ft_close_file(pipe_fd[0], NULL);
			ft_error_dup(pipex);
		}
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		{
			ft_close_file(pipex->outfile_fd, argv[4]);
			ft_close_file(pipe_fd[0], NULL);
			ft_error_dup(pipex);
		}
		ft_close_file(pipex->outfile_fd, argv[4]);
		ft_close_file(pipe_fd[0], NULL);
		pipex->cmd = ft_get_cmd(argv[pipex->argc - 2]);
		if (!pipex->cmd)
		{
			ft_free_array(pipex->bin_path);
			perror("./pipex");
			exit (ERR_MEMORY_ALLOCATE);
		}
		ft_exec_without_path(pipex, envp, pipex->cmd);
		ft_exec_with_path(pipex, envp, pipex->cmd);
		ft_error(pipex->cmd[0], "Command not found");
		ft_free_pipex(pipex);
		exit(ERR_EXECUTE_CMD);
	}
}
