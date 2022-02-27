/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/27 20:02:43 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// leaks ...
// catch error code from child processes

// am-j2% < infile not-cat grep > outfile
// zsh: command not found: not-cat

static void	ft_check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex: ERR_NUMBER_ARG\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_check_argc(argc);
	if (pipe(pipex.fd) == -1)
	{
		perror("./pipex: ");
		exit(ERR_PIPE);
	}
	ft_open_files(&pipex, argv);
	ft_parser(&pipex, argv, envp);
	ft_child(&pipex, envp);
	ft_free_pipex(&pipex);
	ft_close_file(pipex.infile_fd);
	ft_close_file(pipex.outfile_fd);
	ft_close_file(pipex.fd[0]);
	ft_close_file(pipex.fd[1]);
	waitpid(pipex.child[0], NULL, 0);
	return (0);
}
