/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:55:14 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/11 21:38:53 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_check_argc(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("./pipex: Invalid number of arguments\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

static void	ft_wait_childs(t_pipex *pipex)
{
	int	i;
	int	*status;

	i = 0;
	status = (int *)malloc(sizeof(int) * (pipex->argc - 3));
	if (!status)
		exit(ERR_MEMORY_ALLOCATE);
	while (i < pipex->argc - 3)
	{
		if (wait(&(status[i])) == -1)
			ft_error(NULL, strerror(errno));
		i++;
	}
	i--;
	while (i >= 0)
	{
		if (WIFEXITED(status[i]) != 0)
			exit (WEXITSTATUS(status[i]));
		i--;
	}
	free(status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	pipex.argc = argc;
	pipex.envp = envp;
	ft_check_argc(argc);
	if (pipe(pipex.pipe1) == -1)
	{
		perror("./pipex: ");
		exit(ERR_PIPE);
	}
	pipex.bin_path = ft_get_path(envp);
	i = ft_child(&pipex, argv, envp);
	ft_free_array(pipex.bin_path);
	ft_close_last_pipe(&pipex, i);
	ft_wait_childs(&pipex);
	return (0);
}
