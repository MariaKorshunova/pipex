/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:54:27 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 19:48:06 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_child_first(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->fd[0], NULL);
	ft_open_infile(pipex, argv);
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

static void	ft_child_last(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->fd[1], NULL);
	ft_open_outfile(pipex, argv);
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

void	ft_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->child[0] = fork();
	if (pipex->child[0] < 0)
		ft_error_fork(pipex);
	else if (pipex->child[0] == 0)
		ft_child_first(pipex, argv, envp);
	pipex->child[1] = fork();
	if (pipex->child[1] < 0)
		ft_error_fork(pipex);
	else if (pipex->child[1] == 0)
		ft_child_last(pipex, argv, envp);
}
