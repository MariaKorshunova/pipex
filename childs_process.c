/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:04 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/20 19:52:28 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_1(t_pipex	*pipex, char **envp)
{
	// int		status;
	char	*array[] = {"cat", "-n", NULL};

	dup2(pipex->infile_fd, STDIN_FILENO);
	close(pipex->infile_fd);
	if (access(pipex->cmd1[0], 01) == 0)
		execve(pipex->cmd1[0], pipex->cmd1, envp);
	// status = access("usr/bin/wc", 01);
	// printf("status=%d\n", status);
	execve("cat", array, envp);
	// execve("/bin/cat", NULL, NULL);
}
