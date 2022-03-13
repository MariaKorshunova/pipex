/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:50:18 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/13 17:11:18 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_error_line(t_pipex *pipex)
{
	ft_free_array(pipex->bin_path);
	ft_close_file(pipex->pipe1[0], NULL);
	ft_close_file(pipex->pipe1[1], NULL);
	perror("./pipex");
	exit (ERR_MEMORY_ALLOCATE);
}

static void	ft_read_line(t_pipex *pipex, char **argv)
{
	char	*line;
	int		eof;
	int		len_limiter;

	eof = 1;
	len_limiter = ft_strlen(argv[2]);
	while (eof)
	{
		ft_putstr_fd("pipex here_doc>", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			ft_error_line(pipex);
		if (ft_strncmp(line, argv[2], len_limiter) == 0
			&& line[len_limiter] == '\n')
		{
			free(line);
			eof = 0;
		}
		else
		{
			ft_putstr_fd(line, pipex->pipe2[1]);
			free(line);
		}
	}
}

void	ft_heredoc(t_pipex *pipex, char **argv)
{
	if (pipe(pipex->pipe2) == -1)
		ft_error_pipe(pipex, 1);
	ft_read_line(pipex, argv);
	ft_child_middle(pipex, argv[3], pipex->pipe2, pipex->pipe1);
	ft_close_file(pipex->pipe2[0], NULL);
	ft_close_file(pipex->pipe2[1], NULL);
}
