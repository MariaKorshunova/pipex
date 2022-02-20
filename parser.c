/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:01:50 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/20 17:02:22 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parser(t_pipex *pipex, char **argv, char **envp)
{
	pipex->bin_path = ft_get_path(envp);
	pipex->cmd1 = ft_get_cmd(argv[2]);
	if (!pipex->cmd1)
	{
		ft_free_array(pipex->bin_path);
		ft_putstr_fd("ERR_READ_CMD\n", 2);
		exit (ERR_READ_CMD);
	}
}

char	**ft_get_path(char **envp)
{
	int		i;
	char	**bin_path;

	if (!envp)
		return (NULL);
	if (!(*envp))
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	bin_path = ft_split(envp[i] + 5, ':');
	return (bin_path);
}

char	**ft_get_cmd(char *argv)
{
	char	**cmd;

	if (!argv)
		return (NULL);
	cmd = ft_split(argv, ' ');
	return (cmd);
}
