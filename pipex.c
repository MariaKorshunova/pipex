/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/21 18:53:56 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("ERR_NUMBER_ARG\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	child_1;

	ft_check_argc(argc);
	ft_open_files(&pipex, argv);
	ft_parser(&pipex, argv, envp);
	child_1 = fork();
	if (child_1 < 0)
	{
		perror ("");
		exit (ERR_FORK);
	}
	else if (child_1 == 0)
		ft_child_1(&pipex, envp);
	printf("PID parent process: %d\n", getpid());
	ft_free_pipex(&pipex);
	ft_close_file(pipex.infile_fd);
	ft_close_file(pipex.outfile_fd);
	//catch error code from child processes
	waitpid(child_1, NULL, 0);
	return (0);
}
