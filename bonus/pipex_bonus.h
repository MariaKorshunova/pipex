/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:39:41 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/13 15:26:17 by jmabel           ###   ########.fr       */
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

# include "get_next_line.h"

# define ERR_NUMBER_ARG 1
# define ERR_MEMORY_ALLOCATE 2
# define ERR_FILE 3
# define ERR_READ_CMD 4
# define ERR_EXECUTE_CMD 127
# define ERR_FORK 6
# define ERR_DUP 7
# define ERR_EXEC 8
# define ERR_PIPE 9

# define PATH "PATH="

typedef struct s_pipex
{
	int		argc;
	int		infile_fd;
	int		outfile_fd;
	int		heredoc;
	int		pipe1[2];
	int		pipe2[2];
	pid_t	child;
	char	**envp;
	char	**bin_path;
	char	**cmd;
}		t_pipex;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp_exact_match(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);

void	ft_open_infile(t_pipex *pipex, char **argv);
void	ft_open_outfile(t_pipex *pipex, char **argv);
void	ft_close_file(int fd, char *name);
void	ft_close_last_pipe(t_pipex *pipex, int i);

char	**ft_get_path(t_pipex *pipex, char **envp);
void	ft_get_cmd(t_pipex *pipex, char *argv);
void	ft_exec(t_pipex *pipex, char *n_argv, char **envp);

void	ft_child_first(t_pipex	*pipex, char **argv, char **envp);
void	ft_manage_middle_child(t_pipex *pipex, char **argv, int *i);
void	ft_child_middle(t_pipex *pipex, char *n_argv, int *fd1, int *fd2);
void	ft_child_last(t_pipex *pipex, char **argv, int *fd);

void	ft_heredoc(t_pipex *pipex, char **argv);

void	ft_error(char *name, char *str_error);
void	ft_error_dup(t_pipex *pipex);
void	ft_error_open_file(t_pipex *pipex, int fd);
void	ft_error_fork(t_pipex *pipex, int *pipefd, int both);
void	ft_error_pipe(t_pipex *pipex, int flag_pipefd);

void	ft_free_array(char **arr);
void	ft_free_pipex(t_pipex *pipex);

#endif