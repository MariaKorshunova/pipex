/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:34 by jmabel            #+#    #+#             */
/*   Updated: 2022/02/14 16:18:54 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//0777 (int 511) -r-x--x--x

int	main(int argc, char *argv[])
{
	int	pid;
	int	err;
	int	wstatus;
	int	status_code;
	int	file;
	int	file2;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (2);
		file2 = dup2(file, 1);
		printf("The fd of ping results=%d\n", file2);
		close(file);
		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
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
