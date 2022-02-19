/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/19 19:58:14 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_get_path(char **envp)
{
	int		i;
	char	**bin_path;

	if (!envp)
		return (NULL);
	if (!(*envp))
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	bin_path = ft_split(envp[i] + 5, ':');
	return (bin_path);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		number_str_in_array;

	if (argc != 5)
	{
		ft_putstr_fd("ERR_NUMBER_ARG\n", 2);
		exit (ERR_NUMBER_ARG);
	}
	pipex.infile_fd = open(argv[1], O_RDONLY);
	if (pipex.infile_fd == -1)
	{
		perror ("ERR_OPEN");
		exit (ERR_OPEN);
	}
	pipex.bin_path = ft_get_path(envp);
	number_str_in_array = 0;
	while (pipex.bin_path[number_str_in_array] != NULL)
		number_str_in_array++;
	ft_free_array(pipex.bin_path, number_str_in_array + 1);
	// pipex->cmd1 = ft_get_cmd1(argv[2]);
	// pid1 = fork();
	// if (pid1 == -1)
	// {
	// 	// ft_putendl_fd("Error with fork", 2);
	// 	return (3);
	// }
	// else if (pid1 == 0)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execl("/bin/ls", "/bin/ls", NULL);
	// }
	// pid2 = fork();
	// if (pid2 == -1)
	// {
	// 	// ft_putendl_fd("Error with fork", 2);
	// 	return (3);
	// }
	// else if (pid2 == 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execlp("grep", "grep", "libft", NULL);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	return (0);
}
