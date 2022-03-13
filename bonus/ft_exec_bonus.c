/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:54:50 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/13 12:50:04 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_strjoin_with_endchar(char const *s1, char const *s2, char c)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = c;
	j = i + 1;
	i = 0;
	while (i < ft_strlen(s2))
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}

static void	ft_exec_without_path(t_pipex *pipex, char **envp, char **cmd)
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
		cmd_with_path = ft_strjoin_with_endchar(pipex->bin_path[i],
				cmd[0], '/');
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

void	ft_exec(t_pipex *pipex, char *n_argv, char **envp)
{
	ft_get_cmd(pipex, n_argv);
	ft_exec_without_path(pipex, envp, pipex->cmd);
	ft_exec_with_path(pipex, envp, pipex->cmd);
	ft_error(pipex->cmd[0], "Command not found");
	ft_free_pipex(pipex);
	exit(ERR_EXECUTE_CMD);
}
