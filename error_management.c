/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:22:02 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/13 19:22:09 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	pid;
	int	err;
	int	wstatus;
	int	status_code;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		err = execlp("ping", "ping", "-c", "3", "google.con", NULL);
		if (err == -1)
		{
			printf("Could not find program to execute!\n");
			return (2);
		}
	}
	else
	{
		wait(&wstatus);
		if (WIFEXITED (wstatus))
		{
			status_code = WEXITSTATUS (wstatus);
			if (status_code == 0)
				printf("Success!\n");
			else
				printf("Failure with status code %d\n", status_code);
		}
		printf("Some post processing goes here!\n");
	}
	return (0);
}
