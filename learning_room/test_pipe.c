#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main()
{
	int		pid;
	int		pipe_fds[2];
	char	buffer[225];

	//pipe(array_of_int)
	if (pipe(pipe_fds) == -1)
	{
		printf("pipe ---> failure\n");
		exit (1);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("pipe ---> failure\n");
		exit (1);
	}
	else if (pid == 0) //child process
	{
		close(pipe_fds[1]);
		read(pipe_fds[0], buffer, ft_strlen(buffer));
		printf("the input received by the read system call --> %s\n", buffer);
		close(pipe_fds[0]);
		return (0);
	}
	else //parent process
	{
		close(pipe_fds[0]);
		write(pipe_fds[1], "The parent is here \n", ft_strlen("The parent is here \n"));
		close(pipe_fds[1]);
		return (0);
	}
}