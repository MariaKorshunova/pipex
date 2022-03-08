/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:48 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/08 16:52:00 by jmabel           ###   ########.fr       */
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

# define PATH "PATH="

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd1[2];
	int		pipe_fd2[2];
	int		argc;
	pid_t	child;
	char	**bin_path;
	char	**cmd;
}		t_pipex;

# define ERR_NUMBER_ARG 1
# define ERR_MEMORY_ALLOCATE 2
# define ERR_FILE 3
# define ERR_READ_CMD 4
# define ERR_EXECUTE_CMD 5
# define ERR_FORK 6
# define ERR_DUP 7
# define ERR_EXEC 8
# define ERR_PIPE 9

void	ft_open_files(t_pipex *pipex, char **argv);
void	ft_close_file(int fd, char *name);

char	**ft_get_path(char **envp);
char	**ft_get_cmd(char *argv);

void	ft_child_first(t_pipex *pipex, char **argv, char **envp);
void	ft_child_last(t_pipex *pipex, int *pipe_fd, char **argv, char **envp);
void	ft_exec_without_path(t_pipex *pipex, char **envp, char **cmd);
void	ft_exec_with_path(t_pipex *pipex, char **envp, char **cmd);
void	ft_exec(t_pipex *pipex, char *cmd, char **envp);

void	ft_error(char *name, char *str_error);
void	ft_error_dup(t_pipex *pipex);

void	ft_free_pipex(t_pipex *pipex);
void	ft_free_array(char **arr);

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif