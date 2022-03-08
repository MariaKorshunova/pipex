/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 18:47:43 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex: Invalid number of arguments\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

static void	ft_waitpid(t_pipex *pipex, int *status_0, int *status_1)
{
	if (pipex->child[0] > 0)
	{
		if (waitpid(pipex->child[0], status_0, 0) == -1)
			ft_error(NULL, strerror(errno));
	}
	if (pipex->child[1] > 0)
	{
		if (waitpid(pipex->child[1], status_1, 0) == -1)
			ft_error(NULL, strerror(errno));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status[2];

	ft_check_argc(argc);
	if (pipe(pipex.fd) == -1)
	{
		perror("./pipex: ");
		exit(ERR_PIPE);
	}
	ft_open_files(&pipex, argv);
	ft_parser(&pipex, argv, envp);
	ft_child(&pipex, argv, envp);
	ft_free_pipex(&pipex);
	ft_close_file(pipex.infile_fd, argv[1]);
	ft_close_file(pipex.outfile_fd, argv[4]);
	ft_close_file(pipex.fd[0], NULL);
	ft_close_file(pipex.fd[1], NULL);
	ft_waitpid(&pipex, &status[0], &status[1]);
	if (WIFEXITED(status[1]) != 0)
		return (WEXITSTATUS(status[1]));
	return (0);
}
