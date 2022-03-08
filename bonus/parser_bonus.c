/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:55:09 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 18:39:08 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_get_path(char **envp)
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
		perror("./pipex: ");
		exit (ERR_MEMORY_ALLOCATE);
	}
	return (bin_path);
}

char	**ft_get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	return (cmd);
}
