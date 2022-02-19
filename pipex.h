/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:39:41 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/19 19:55:08 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
// # include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define ERR_NUMBER_ARG 1
# define ERR_OPEN 2

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	char	**bin_path;
	char	**cmd1;
}		t_pipex;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_array(char **arr, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif