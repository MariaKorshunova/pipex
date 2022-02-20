/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/20 19:41:12 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	child_1;

	if (argc != 5)
	{
		ft_putstr_fd("ERR_NUMBER_ARG\n", 2);
		exit (ERR_NUMBER_ARG);
	}
	pipex.infile_fd = open(argv[1], O_RDONLY);
	if (pipex.infile_fd == -1)
	{
		perror ("ERR_OPEN");
		exit (ERR_OPEN);
	}
	ft_parser(&pipex, argv, envp);
	child_1 = fork();
	if (child_1 < 0)
	{
		perror ("ERR_FORK");
		exit (ERR_FORK);
	}
	else if (child_1 == 0)
	{
		printf("This is child one \n");
		ft_child_1(&pipex, envp);
	}
	close(pipex.infile_fd);
	waitpid(child_1, NULL, 0);
	ft_free_pipex(&pipex);
	return (0);
}
