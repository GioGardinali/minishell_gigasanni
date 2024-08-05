#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char const *argv[])
{
	int	pid;
	int	pid2;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/ls", (char *[]) {"ls", "-l", NULL}, 0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		execve("/usr/bin/tr", (char *[]) {"tr", "a-z", "A-Z", NULL}, 0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, 0, 0);
	waitpid(pid2, 0, 0);
	return (0);
}
