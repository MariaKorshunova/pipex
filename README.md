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


### wait

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


//execve
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
//fork
    int id;
    int id1;
    id = fork();
    id1 = fork();
    printf("Hello world from id=%d and id1=%d, \n", id, id1);
    return (0);# Pipex: simulating the pipe "|" operator in C

    pid_t	pid;
	pid = fork();
	if (pid)
		wait(NULL);
	return (write(1, "a", 1));


## Question with fork

Solving sync problems

    pid_t	pid;
	pid = fork();
	if (pid)
		wait(NULL);
	return (write(1, "a", 1));