/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/28 19:39:24 by jmabel           ###   ########.fr       */
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

void	ft_error(char *name)
{
	char	*str_error;
	
	str_error = strerror(errno);
	ft_putstr_fd("./pipex: ", 2);
	ft_putstr_fd(str_error, 2);
	if (name)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
	}
	ft_putstr_fd("\n", 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status[2];

	ft_check_argc(argc);
	if (pipe(pipex.fd) == -1)
	{
		perror("./pipex");
		exit(ERR_PIPE);
	}
	ft_open_files(&pipex, argv);
	ft_parser(&pipex, argv, envp);
	ft_child(&pipex, argv, envp, &(status[0]));
	ft_free_pipex(&pipex);
	ft_close_file(pipex.infile_fd, argv[1]);
	ft_close_file(pipex.outfile_fd, argv[4]);
	ft_close_file(pipex.fd[0], NULL);
	ft_close_file(pipex.fd[1], NULL);
	waitpid(pipex.child[1], &(status[1]), 0);
;	if (WIFEXITED(status[0]) == 0)
		return (WEXITSTATUS(status[0]));
	if (WIFEXITED(status[1]) == 0)
		return (WEXITSTATUS(status[1]));
	return (0);
}
