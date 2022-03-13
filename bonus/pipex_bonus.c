/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:55:14 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/13 17:35:58 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_check_argc(int argc, int heredoc)
{
	int	count;

	if (heredoc == 1)
		count = 6;
	else
		count = 5;
	if (argc < count)
	{
		ft_putstr_fd("./pipex: Invalid number of arguments\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

static int	ft_child(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 0;
	if (pipex->heredoc == 1)
		ft_heredoc(pipex, argv);
	else
		ft_child_first(pipex, argv, envp);
	ft_manage_middle_child(pipex, argv, &i);
	if (i % 2 == 0)
		ft_child_last(pipex, argv, pipex->pipe1);
	else
		ft_child_last(pipex, argv, pipex->pipe2);
	return (i);
}

static void	ft_wait_childs(t_pipex *pipex)
{
	int	i;
	int	*status;
	int	cmd;

	i = 0;
	if (pipex->heredoc == 1)
		cmd = pipex->argc - 4;
	else
		cmd = pipex->argc - 3;
	status = (int *)malloc(sizeof(int) * cmd);
	if (!status)
		exit(ERR_MEMORY_ALLOCATE);
	while (i < cmd)
	{
		if (wait(&(status[i])) == -1)
			ft_error(NULL, strerror(errno));
		i++;
	}
	while (i > 0)
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
	if (ft_strncmp_exact_match(argv[1], "here_doc") == 0)
		pipex.heredoc = 1;
	else
		pipex.heredoc = 0;
	ft_check_argc(argc, pipex.heredoc);
	if (pipe(pipex.pipe1) == -1)
	{
		perror("./pipex: ");
		exit(ERR_PIPE);
	}
	pipex.bin_path = ft_get_path(&pipex, envp);
	i = ft_child(&pipex, argv, envp);
	ft_free_array(pipex.bin_path);
	ft_close_last_pipe(&pipex, i);
	ft_wait_childs(&pipex);
	return (0);
}
