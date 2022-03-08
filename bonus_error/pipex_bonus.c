/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:34:06 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 17:34:29 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex: Invalid number of arguments\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		status;

	pipex.argc = argc;
	i = 0;
	ft_check_argc(argc);
	if (pipe(pipex.pipe_fd1) == -1)
	{
		perror("./pipex: ");
		exit(ERR_PIPE);
	}
	ft_open_files(&pipex, argv);
	pipex.bin_path = ft_get_path(envp);
	ft_child_first(&pipex, argv, envp);
	ft_child_last(&pipex, (int *)pipex.pipe_fd1, argv, envp);
	ft_free_array(pipex.bin_path);
	ft_close_file(pipex.infile_fd, argv[1]);
	ft_close_file(pipex.outfile_fd, argv[argc - 1]);
	ft_close_file(pipex.pipe_fd1[0], NULL);
	ft_close_file(pipex.pipe_fd1[1], NULL);
	while (i > 0)
	{
		wait(&status);
		i--;
	}
	if (WIFEXITED(status) != 0)
		return (WEXITSTATUS(status));
	return (0);
}
