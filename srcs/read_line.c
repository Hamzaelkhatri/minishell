#include "../includes/minishell.h"

char	*read_line(void)
{
	char *line;
	char r;
	int i = 0;
	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line)
	{
		write(1, "minishell : allocation error\n", 30);
		exit(0);
	}
	if ((r = read(0, line, BUFFER_SIZE)) == -1)
	{
		if (line[BUFFER_SIZE] == '\0')
			exit(0);
		else
			exit(-1);
	}
	line[r-1] = '\0';
	
	// while(line[i])
		// printf("%c",line[i++]);
	// printf("%lu\n",ft_strlen(line));
	// printf("%s\n",line);
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
		if (!a)//a != 0
		{
			char *cmd[] = {"/bin/stty", 0 };
			char *cmd_args[] = { "stty", "-echoctl", 0 };
			char *env[] = {" ", "env", 0};
			execve(cmd[0], cmd_args, env);
			// execve()
		}
	}
}

void split_line(char *line)
{
	char **tab;
	tab = ft_space_split(line);
	int i;

	i = 1;
	if(ft_str_in_str("echo",tab[0]))
	{
		if(ft_2strlen(tab) == 1)
			write(1,"\n",1);
		else
		{
			if(ft_2strlen(tab) == 2)
				ft_putstr_fd(tab[1],1);
			else
			{
				while(i < ft_2strlen(tab))
				{
					ft_putstr_fd(tab[i++],1);
					if(i < ft_2strlen(tab))
					write(1," ",1);
				}
			}
			write(1,"\n",1);
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
		write(1, "bash$", 6);
		line = read_line();
		if(line[0]=='\0')
		{
			write(1, "exit ", 4);
			exit(1);
		}
		split_line(line);
		free(line);
	}
}