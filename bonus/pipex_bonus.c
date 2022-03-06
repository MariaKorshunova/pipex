/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:34:06 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/06 17:59:01 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_check_argc(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("./pipex: Invalid number of arguments\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	(void)envp;
	(void)argv;
	ft_check_argc(argc);
	// ft_open_files(&pipex, argv);
	return (0);
}
