/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:04 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/07 15:15:36 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_error_dup(t_pipex *pipex)
{
	ft_free_pipex(pipex);
	perror("./pipex");
	exit(ERR_DUP);
}

static void	ft_error_open_file(t_pipex *pipex, int fd)
{
	ft_free_pipex(pipex);
	ft_close_file(fd, NULL);
	exit (ERR_FILE);
}

static void	ft_child_0(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->outfile_fd, argv[4]);
	ft_close_file(pipex->fd[0], NULL);
	if (pipex->infile_fd == -1)
		ft_error_open_file(pipex, pipex->fd[1]);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
	{
		ft_close_file(pipex->infile_fd, argv[1]);
		ft_close_file(pipex->fd[1], NULL);
		ft_error_dup(pipex);
	}
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
	{
		ft_close_file(pipex->infile_fd, argv[1]);
		ft_close_file(pipex->fd[1], NULL);
		ft_error_dup(pipex);
	}
	ft_close_file(pipex->infile_fd, argv[1]);
	ft_close_file(pipex->fd[1], NULL);
	ft_exec_without_path(pipex, envp, pipex->cmd1);
	ft_exec_with_path(pipex, envp, pipex->cmd1);
	ft_error(pipex->cmd1[0], "Command not found");
	ft_free_pipex(pipex);
	exit(ERR_EXECUTE_CMD);
}

static void	ft_child_1(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->infile_fd, argv[1]);
	ft_close_file(pipex->fd[1], NULL);
	if (pipex->outfile_fd == -1)
		ft_error_open_file(pipex, pipex->fd[0]);
	if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
	{
		ft_close_file(pipex->outfile_fd, argv[4]);
		ft_close_file(pipex->fd[0], NULL);
		ft_error_dup(pipex);
	}
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
	{
		ft_close_file(pipex->outfile_fd, argv[4]);
		ft_close_file(pipex->fd[0], NULL);
		ft_error_dup(pipex);
	}
	ft_close_file(pipex->outfile_fd, argv[4]);
	ft_close_file(pipex->fd[0], NULL);
	ft_exec_without_path(pipex, envp, pipex->cmd2);
	ft_exec_with_path(pipex, envp, pipex->cmd2);
	ft_error(pipex->cmd2[0], "Command not found");
	ft_free_pipex(pipex);
	exit(ERR_EXECUTE_CMD);
}

void	ft_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->child[0] = fork();
	if (pipex->child[0] < 0)
	{
		perror ("./pipex: ");
		exit (ERR_FORK);
	}
	else if (pipex->child[0] == 0)
		ft_child_0(pipex, argv, envp);
	pipex->child[1] = fork();
	if (pipex->child[1] < 0)
	{
		perror ("./pipex: ");
		exit (ERR_FORK);
	}
	else if (pipex->child[1] == 0)
		ft_child_1(pipex, argv, envp);
}
