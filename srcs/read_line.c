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
void get_env_variables(void)
{
	char *argv[2];
	argv[0] = "env";
	argv[1] = NULL;
	execve(argv[0],argv,NULL);
}

void	loop_shell(void)
{
	char	*line;
	char	**args;
	int		status;
	char	**env_variables;
	status = 1;
	//while (status)
	//{
		//line = read_line();
		//env_variables = 
		get_env_variables();
		
		write(1, "bash$ ", 6);
		//free(line);
	//}
}
