/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:17:13 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 16:51:19 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exec_without_path(t_pipex *pipex, char **envp, char **cmd)
{
	if (access(cmd[0], 01) == 0)
	{
		execve(cmd[0], cmd, envp);
		ft_free_pipex(pipex);
		perror("./pipex: ");
		exit(ERR_EXEC);
	}
	if (!pipex->bin_path)
	{
		ft_free_pipex(pipex);
		exit(ERR_EXEC);
	}
}

void	ft_exec_with_path(t_pipex *pipex, char **envp, char **cmd)
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
			perror("./pipex: ");
			exit (ERR_MEMORY_ALLOCATE);
		}
		if (access(cmd_with_path, 01) == 0)
		{
			execve(cmd_with_path, cmd, envp);
			ft_free_pipex(pipex);
			free(cmd_with_path);
			perror("./pipex: ");
			exit(ERR_EXEC);
		}
		free(cmd_with_path);
		i++;
	}
}

void	ft_exec(t_pipex *pipex, char *cmd, char **envp)
{
	pipex->cmd = ft_get_cmd(cmd);
	if (!pipex->cmd)
	{
		ft_free_array(pipex->bin_path);
		perror("./pipex");
		exit (ERR_MEMORY_ALLOCATE);
	}
	ft_exec_without_path(pipex, envp, pipex->cmd);
	ft_exec_with_path(pipex, envp, pipex->cmd);
}
