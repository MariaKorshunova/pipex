/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:34:06 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/07 20:28:33 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_check_argc(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("./pipex: Invalid number of arguments\n", 2);
		exit (1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		status;

	i = 0;
	ft_check_argc(argc);
	if (pipe(pipex.pipe_fd1) == -1)
	{
		perror("./pipex: ");
		exit(errno);
	}
	ft_open_files(&pipex, argv);
	if (dup2(pipex.infile_fd, STDIN_FILENO) == -1)
	{
		ft_close_file(pipex.infile_fd, argv[1]);
		ft_close_file(pipex.outfile_fd, argv[argc - 1]);
		ft_close_file(pipex.pipe_fd1[0], NULL);
		ft_close_file(pipex.pipe_fd1[1], NULL);
		perror("./pipex: ");
		exit(errno);
	}
	pipex.bin_path = ft_get_path(envp);
	while (i < argc - 3)
	{
		if (i % 2 == 0)
		{
			pipe(pipex.pipe_fd2);
			pipex.child = fork();
			if (pipex.child < 0)
				perror("");
			else if (pipex.child == 0)
			{
				ft_close_file(pipex.pipe_fd1[0], NULL);
				if (i == argc - 4)
					dup2(pipex.outfile_fd, STDOUT_FILENO); //ошибка dup
				else
					dup2(pipex.pipe_fd2[1], STDOUT_FILENO); //ошибка dup
				ft_close_file(pipex.pipe_fd1[1], NULL);
				pipex.cmd = ft_get_cmd(argv[i + 2]); // проверить маллок
				ft_close_file(pipex.outfile_fd, argv[argc - 1]);
				ft_close_file(pipex.infile_fd, argv[1]);
				ft_exec_without_path(&pipex, envp, pipex.cmd);
				ft_exec_with_path(&pipex, envp, pipex.cmd);
				// ошибка exec
			}
			else
			{
				ft_close_file(pipex.pipe_fd1, NULL);
				pipe(pipex.pipe_fd2);
				dup2(pipex.pipe_fd[0], STDIN_FILENO);
				i++;
			}
		}
	}
	free(pipex.bin_path);
	ft_close_file(pipex.infile_fd, argv[1]);
	ft_close_file(pipex.outfile_fd, argv[argc - 1]);
	ft_close_file(pipex.pipe_fd[0], NULL);
	ft_close_file(pipex.pipe_fd[1], NULL);
	while (i > 0)
	{
		wait(&status);
		i--;
	}
	return (0);
}
