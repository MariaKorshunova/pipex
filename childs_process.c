/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:04 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/02 21:46:29 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_without_path(t_pipex *pipex, char **envp, char **cmd)
{
	if (access(cmd[0], 01) == 0)
	{
		execve(cmd[0], cmd, envp);
		ft_free_pipex(pipex);
		perror("./pipex");
		exit(ERR_EXEC);
	}
	if (!pipex->bin_path)
	{
		ft_free_pipex(pipex);
		exit(ERR_EXECUTE_CMD);
	}
}

static void	ft_exec_with_path(t_pipex *pipex, char **envp, char **cmd)
{
	int		i;
	char	*cmd_with_path;

	i = 0;
	while (pipex->bin_path[i] != NULL)
	{
		cmd_with_path = ft_strjoin_slash(pipex->bin_path[i], cmd[0]);
		if (!cmd_with_path)
		{
			ft_free_pipex(pipex);
			perror("./pipex");
			exit (ERR_MEMORY_ALLOCATE);
		}
		if (access(cmd_with_path, 01) == 0)
		{
			execve(cmd_with_path, cmd, envp);
			ft_free_pipex(pipex);
			free(cmd_with_path);
			perror("./pipex");
			exit(ERR_EXEC);
		}
		free(cmd_with_path);
		i++;
	}
}

// static void	ft_dup2(t_pipex	*pipex, int fd, char *name)
// {
// 	if (dup2(pipex->infile_fd, fd) == -1)
// 	{
// 		ft_close_file(pipex->infile_fd, name);
// 		ft_close_file(pipex->fd[1], NULL);
// 		ft_free_pipex(pipex);
// 		perror("./pipex");
// 		exit(ERR_DUP);
// 	}	
// }

static void	ft_child_0(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->outfile_fd, argv[4]);
	ft_close_file(pipex->fd[0], NULL);
	// ft_dup2(pipex, STDIN_FILENO, argv[1]);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
	{
		ft_close_file(pipex->infile_fd, argv[1]);
		ft_close_file(pipex->fd[1], NULL);
		ft_free_pipex(pipex);
		perror("./pipex");
		exit(ERR_DUP);
	}
	if (pipex->outfile_fd != -1)
	{
		// ft_dup2(pipex, STDOUT_FILENO, argv[1]);
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		{
			ft_close_file(pipex->infile_fd, argv[1]);
			ft_close_file(pipex->fd[1], NULL);
			ft_free_pipex(pipex);
			perror("./pipex");
			exit(ERR_DUP);
		}
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
	if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
	{
		ft_close_file(pipex->outfile_fd, argv[4]);
		ft_close_file(pipex->fd[0], NULL);
		ft_free_pipex(pipex);
		perror("./pipex");
		exit(ERR_DUP);
	}
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
	{
		ft_close_file(pipex->outfile_fd, argv[4]);
		ft_close_file(pipex->fd[0], NULL);
		ft_free_pipex(pipex);
		perror("./pipex");
		exit(ERR_DUP);
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
	if (pipex->infile_fd != -1)
	{
		pipex->child[0] = fork();
		if (pipex->child[0] < 0)
		{
			perror ("./pipex");
			exit (ERR_FORK);
		}
		else if (pipex->child[0] == 0)
			ft_child_0(pipex, argv, envp);
	}
	if (pipex->outfile_fd != -1)
	{
		pipex->child[1] = fork();
		if (pipex->child[1] < 0)
		{
			perror ("./pipex");
			exit (ERR_FORK);
		}
		else if (pipex->child[1] == 0)
			ft_child_1(pipex, argv, envp);
	}
}
