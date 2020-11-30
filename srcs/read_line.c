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

void	loop_shell(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		write(1, "bash$ ", 6);
		line = read_line();
		free(line);
	}
}
