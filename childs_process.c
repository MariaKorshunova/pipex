/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:04 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/21 18:59:02 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_1(t_pipex	*pipex, char **envp)
{
	int		i;
	char	*cmd_with_path;

	i = 0;
	ft_close_file(pipex->outfile_fd);
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
	{
		ft_close_file(pipex->infile_fd);
		ft_free_pipex(pipex);
		perror("");
		exit(ERR_DUP);
	}
	ft_close_file(pipex->infile_fd);
	if (access(pipex->cmd1[0], 01) == 0)
	{
		execve(pipex->cmd1[0], pipex->cmd1, envp);
		ft_free_pipex(pipex);
		perror("");
		exit(ERR_EXEC);
	}
	if (!pipex->bin_path)
	{
		ft_free_pipex(pipex);
		exit(ERR_EXECUTE_CMD);
	}
	while (pipex->bin_path[i] != NULL)
	{
		cmd_with_path = ft_strjoin_slash(pipex->bin_path[i], pipex->cmd1[0]);
		if (!cmd_with_path)
		{
			ft_free_pipex(pipex);
			perror("");
			exit (ERR_MEMORY_ALLOCATE);
		}
		if (access(cmd_with_path, 01) == 0)
		{
			execve(cmd_with_path, pipex->cmd1, envp);
			ft_free_pipex(pipex);
			free(cmd_with_path);
			perror("");
			exit(ERR_EXEC);
		}
		free(cmd_with_path);
		i++;
	}
	ft_free_pipex(pipex);
	exit(ERR_EXECUTE_CMD);
}
