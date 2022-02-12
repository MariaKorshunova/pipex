/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/12 17:58:49 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(void)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid)
		wait(NULL);
	return (write(1, "a", 1));
}
