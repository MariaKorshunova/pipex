/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:48 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/07 19:51:50 by jmabel           ###   ########.fr       */
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
	pid_t	child;
	char	**bin_path;
	char	**cmd;
}		t_pipex;

void	ft_open_files(t_pipex *pipex, char **argv);
void	ft_close_file(int fd, char *name);
void	ft_exec_without_path(t_pipex *pipex, char **envp, char **cmd);
void	ft_exec_with_path(t_pipex *pipex, char **envp, char **cmd);

char	**ft_get_path(char **envp);
char	**ft_get_cmd(char *argv);

void	ft_error(char *name, char *str_error);

void	ft_free_pipex(t_pipex *pipex);
void	ft_free_array(char **arr);

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif