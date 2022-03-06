/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:48 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/06 17:59:05 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define ERR_NUMBER_ARG 1
# define ERR_MEMORY_ALLOCATE 2
# define ERR_FILE 3
# define ERR_READ_CMD 4
# define ERR_EXECUTE_CMD 5
# define ERR_FORK 6
# define ERR_DUP 7
# define ERR_EXEC 8
# define ERR_PIPE 9

# define PATH "PATH="

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd1[2];
	int		pipe_fd2[2];
	pid_t	child[2];
	char	**bin_path;
	char	**cmd1;
	char	**cmd2;
}		t_pipex;

void	ft_open_files(t_pipex *pipex, char **argv);
void	ft_close_file(int fd, char *name);

#endif