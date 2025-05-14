#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	if (n == 0)
		return (0);
	if (s1 == NULL && n == 0)
		return (0);
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	i = 0;
	while ((ptr_s1[i] || ptr_s2[i]) && (i < n))
	{
		if (ptr_s1[i] != ptr_s2[i])
			return (ptr_s1[i] - ptr_s2[i]);
		i++;
	}
	return (0);
}

char	*check_str(char *str)
{
	// int	i;
	char	*file_name;

	// i = 0;
	while (*str)
	{
		if (*str == '>')
			break;
		str++;
	}
	if (*str == '\0')
		return (NULL);
	else
	{
		str++;
		file_name = str;
		printf("str --> %s\n", file_name);
	}
	return (file_name);
}

char	*our_input(char *str)
{
	//char	tmp[1000];
	char	*tmp;
	char	*input;
	//int		i;

	// tmp = NULL;
	//i = 0;
	while (*str)
	{
		if ((*str == ' ') || (*str == '\t'))
		{
			//str++;
			break ;
		}
		//tmp[i] = *str;
		//*tmp = *str;
		//tmp++;
		str++;
	}
	tmp = str;
	printf("tmp--> %s\n", tmp);
	if (ft_strncmp("echo", tmp, 4) == 0)
	{
		//input = str;
		//return (input);
		while (*str)
		{
			if (*str == '<')
				break ;
			*input = *str;
			str++;
			input++;
		}
		return (input);
	}
	return (NULL);
}

int	main()
{
	// int		fds[0];
	//int		fds[2];
	int		fd;
	char	*str;
	char	*input;
	char	*file_name;
	pid_t	pid;

	str = "echo hhhhh >file.txt";
	file_name = check_str(str);
	input = our_input(str);
	printf("%s\n", input);
	pid = fork(); //pid == 0 for the child, pid >= 1 for the main or the parent
	if (pid == 0)
	{
		fd = open(file_name, O_CREAT | O_RDWR, 0777);
		if (fd < 0)
		{
			printf("We cannot open the file, SORRY :/\n");
			exit (1);
		}
		dup2(fd, STDOUT_FILENO);
		//printf("test\n");
		printf("%s\n", input);
		close (fd);
		//close (fds[1]);
	}
	else if (pid > 0)
	{
		//fd = 1;
		//dup2(fd, STDOUT_FILENO);
		//printf("%s\n", input);
		//close (fd);
		wait (NULL);
	}
	else
	{
		write(2, "ERROR :|\n", 9);
		exit (1);
	}
}
