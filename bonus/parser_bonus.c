/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:55:09 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/13 12:00:11 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_get_path(t_pipex *pipex, char **envp)
{
	int		i;
	char	**bin_path;
	size_t	len;

	len = ft_strlen(PATH);
	if (!envp)
		return (NULL);
	if (!(*envp))
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], PATH, len))
			break ;
		i++;
	}
	bin_path = ft_split(envp[i] + len, ':');
	if (!bin_path)
	{
		ft_close_file(pipex->pipe1[0], NULL);
		ft_close_file(pipex->pipe1[1], NULL);
		perror("./pipex: ");
		exit (ERR_MEMORY_ALLOCATE);
	}
	return (bin_path);
}

void	ft_get_cmd(t_pipex *pipex, char *argv)
{
	pipex->cmd = ft_split(argv, ' ');
	if (!pipex->cmd)
	{
		ft_free_array(pipex->bin_path);
		perror("./pipex");
		exit (ERR_MEMORY_ALLOCATE);
	}
}
