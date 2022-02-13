# pipex
pipex school42
simulating the pipe "|" operator in C

## The following functions are allow to use

### access -- system call checks the accessibility of the file named by the path argument for the access permissions indicated by the mode argument.

    int         status;
    extern int  errno;
    status = access("README.md", 00);
    printf("%d\n", status);
    printf("%s\n", strerror(errno));

* 00   проверка на существование файла;
* 01   проверка на выполнение;
* 02   проверка разрешения на запись;
* 04   проверка разрешения на чтение;
* 06   проверка разрешения на чтение и запись;


### open -- open files and directories
   #include <fcntl.h>
   int open (const char *path, int flags);

If successful, open() returns a non-negative integer, termed a file descriptor.
It returns -1 on failure, and sets errno to indicate the error.


### unlink -- removes the link named by path from its directory and decrements the link count of the file which was referenced by the link.
    
	#include <unistd.h>
	int unlink (const char *pathname);
    
Upon successful completion, a value of 0 is returned.  Otherwise, a value of -1 is returned and errno is set to indicate the error.


### close -- delete a descriptor

	int close (int fd);

Upon successful completion, a value of 0 is returned.  Otherwise, a value of -1 is returned and the global integer variable errno is set to indicate the error.


### read -- read input

    ssize_t	read(int fildes, void *buf, size_t nbyte);

If successful, the number of bytes actually read is returned.  Upon reading end-of-file, zero is returned.  Otherwise, a -1 is returned and the global variable errno is set to indicate the error.


### write -- write output

    ssize_t	write(int fildes, const void *buf, size_t nbyte);

Upon successful completion the number of bytes which were written is returned.  Otherwise, a -1 is returned and the global variable errno is set to indicate the error.


### malloc -- allocate memory

    void *malloc(size_t size);

If successful, function return a pointer to allocated memory.  If there is an error, they return a NULL pointer and set errno to ENOMEM.


### wait -- wait for process termination

    pid_t   wait(int *stat_loc);

If wait() returns due to a stopped or terminated child process, the process ID of the child is returned to the calling process.  Otherwise, a value of -1 is returned and errno is set to indicate the error.

	int		status;
	pid_t	pid;

	if (!fork())
		return (2);
	pid = wait(&status);
	if (WIFEXITED (status))
		printf ("Process is completed, status = %d\n", WIFEXITED (status));

Любой из первых двух макросов может возвращать значение true (ненулевое) в зависимости от хода завершения процесса. Первый, WIFEXITED, возвращает true, если процесс завершается через вызов _exit(), обычным образом. Соответственно, макрос WEXITSTATUS предоставляет 8 бит младших разрядов и передает их _exit().

Solving sync problems. Task to print in ascending order digits 1-5 (child process) and 6-10 (parent process).

	int		n;
	int		i;
	pid_t	pid;

	pid = fork();
	if (!pid)
		n = 1;
	else
		n = 6;
	if (pid)
		wait (NULL);
	i = n;
	while (i < n + 5)
	{
		printf("%d ", i);
		fflush(stdout);
		i++;
	}
	if (pid)
		printf("\n");
	return (0);

### waitpid -- wait for process termination, specifies the set of child processes for which to wait.

    pid_t waitpid (pid_t pid, int *status, int options);

	int	main(void)
	{
		int		n;
		int		i;
		pid_t	pid1;
		pid_t	pid2;
		pid_t	pid1_result;
		pid_t	pid2_result;

		pid1 = 0;
		pid2 = 0;
		pid1 = fork();
		if (pid1)
			pid2 = fork();
		printf("[%d]pid1=%d\n", getpid(), pid1);
		printf("[%d]pid2=%d\n", getpid(), pid2);
		pid1_result = waitpid(pid1, NULL, 0);
		pid2_result = waitpid(pid2, NULL, 0);
		printf("[%d]Waited %d\n", getpid(), pid1_result);
		printf("[%d]Waited %d\n", getpid(), pid2_result);
		return (0);
	}


### free -- deallocates the memory 

	void	free(void *ptr);


### pipe -- create descriptor pair for interprocess communication

	int	pipe(int fildes[2])

The pipe() function creates a pipe (an object that allows unidirectional data flow) and allocates a pair of file descriptors.
* The first descriptor connects to the read end of the pipe;
* the second connects to the write end.

On successful creation of the pipe, zero is returned. Otherwise, a value of -1 is returned and the variable errno set to indicate the error.

	int	main(int argc, char *argv[])
	{
		int		fd[2];
		int		x;
		pid_t	id;

		if (pipe(fd) == -1)
		{
			printf("Error woth opening the pipe\n");
			return (1);
		}
		id = fork();
		if (id == -1)
		{
			printf("Error with fork\n");
			return (4);
		}
		if (id == 0)
		{
			close(fd[0]);
			printf("Input a number: ");
			scanf("%d", &x);
			if (write(fd[1], &x, sizeof(int)) == -1)
			{
				printf("Error woth opening the writing to the pipe\n");
				return (2);
			}
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			if (read(fd[0], &x, sizeof(int)) == -1)
			{
				printf("Error woth opening the reading from the pipe\n");
				return (3);
			}
			close(fd[0]);
			printf("Got from child process %d", x);
		}
		return (0);
	}

### dup, dup2 -- duplicate an existing file descriptor




### execve -- execute a file

    int	execve(const char *path, char *const argv[], char *const envp[]);
    
As the execve() function overlays the current process image  with a new process image, the successful call  has no process to return to. 
If execve() does return to the calling process, an error has occurred; the return value will be -1 and the global variable errno is set to indicate the error.

	char    *array[] = {"push_swap", "3", "2", NULL};
    write(1, "Hello execv!\n", 13);
    pid = execv("../push_swap_github/push_swap", array);
    ft_putnbr_fd(pid, 1);
    write(1, "\nGoodbuy execv!", 14);


	// Print envp
    i = 0;
    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }

### fork -- create a new process

	pid_t	fork(void);

    int id;
    int id1;
    id = fork();
    id1 = fork();
    printf("Hello world from id=%d and id1=%d, \n", id, id1);
    return (0);


## Useful souces

https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901

https://www.youtube.com/watch?v=6xbLgZpOBi8&t=2s