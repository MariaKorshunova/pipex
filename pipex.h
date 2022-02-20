/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:39:41 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/20 19:50:41 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define ERR_NUMBER_ARG 1
# define ERR_READ_CMD 2
# define ERR_OPEN 3
# define ERR_FORK 4

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	char	**bin_path;
	char	**cmd1;
}		t_pipex;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

void	ft_parser(t_pipex *pipex, char **argv, char **envp);
char	**ft_get_path(char **envp);
char	**ft_get_cmd(char *argv);

void	ft_child_1(t_pipex	*pipex, char **envp);

void	ft_free_array(char **arr);
void	ft_free_pipex(t_pipex *pipex);

#endif