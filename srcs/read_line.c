#include "../includes/minishell.h"

char	*read_line(void)
{
	char *line;

	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line)
	{
		write(1, "minishell : allocation error\n", 30);
		exit(0);
	}
	if (read(0, line, BUFFER_SIZE) == -1)
	{
		if (line[BUFFER_SIZE] == '\0')
			exit(0);
		else
			exit(-1);
	}
	return (line);
}

void sigint_handler(int sig)
{
	int a;

	if(sig == SIGINT)
	{
		signal(SIGINT, sigint_handler);
		write(1, "\nbash$ ", 7);
		a = fork();
		if (!a)
		{
			char *cmd[] = {"/bin/stty", 0 };
			char *cmd_args[] = { "stty", "-echoctl", 0 };
			char *env[] = {" ", "env", 0};
			execve(cmd[0], cmd_args, env);
		}
	}
}

void	loop_shell(void)
{
	char	*line;
	char	**args;
	int		status;
	
	signal(SIGINT, sigint_handler);
	status = 1;
	while (status)
	{
		write(1, "bash$ ", 6);
		line = read_line();
		if(line[0]=='\0')
		{
			write(1, "exit ", 4);
			exit(1);
		}
		free(line);
	}
}