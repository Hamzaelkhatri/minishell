#include "minishell.h"
#include <setjmp.h>
int var_glob;
int var_glob1;

int read_line(t_path *key, char **line)
{
	int ret;
	ret = 0;

	*line = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!line)
	{
		ft_putendl_fd("\e[1;31m bash$ : allocation error\e[0;37m", 1);
		exit(1);
	}
	if ((ret = read(0, *line, BUFFER_SIZE)) == -1)
	{
		if (line[BUFFER_SIZE] == 0)
			exit(0);
		else
			exit(1);
	}
	return (ret);
}

void sigint_handler(int sig)
{
	int a;

	if (sig == SIGINT)
	{
		if (var_glob)
			ft_putstr_fd("\n\e[1;32mbash$ \e[0;37m", 2);
		var_glob = 111;
		var_glob1 = 0;
	}
	if (sig == SIGQUIT)
		var_glob = 111;
}

void bash_promp()
{
	ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 2);
}

void signals()
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cnrtl-C", 2);
	if (signal(SIGQUIT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cntrl-\\", 2);
}

void loop_shell(t_path *path)
{
	char *line;
	int ret;
	int i;
	char *lines;
	t_list_cmd *cmd = NULL;
	int check;

	i = 0;
	var_glob = 0;
	lines = NULL;
	var_glob1 = 0;
	check = 0;
	signals();
	bash_promp();
	while (1)
	{
		i = 0;
		if (check > 0)
			path->dollar = check;
		check = 0;
		ret = 0;
		ret = read_line(path, &line);
		if (line[0] == '\0' && !var_glob1)
		{
			frees(&line);
			ft_putendl_fd("exit", 1);
			exit(EXIT_SUCCESS);
		}

		if (line[ret - 1] != '\n')
		{
			if (lines)
				lines = ft_strjoin(lines, line);
			else
				lines = ft_strdup(line);
			var_glob1 = 1;
		}
		else if (lines && var_glob1)
		{
			lines = ft_strjoin(lines, line);
			line = ft_strdup(lines);
			frees(&lines);
			var_glob1 = 0;
		}
		if (line[0] == '\n')
		{
			check = -1;
			var_glob1 = 0;
			frees(&lines);
		}
		if (!var_glob1)
		{
			var_glob = 0;
			path->cmds = line;
			if (check != 0)
				while (line[i] && line[i] == ' ')
					i++;
			if (line[i] != '\n')
			{
				path->cmds = ft_strtrim(path->cmds, "\n");
				check = ft_check_line(path->cmds);
				ft_putnbr_fd(check,2);
			}
			if (!check)
			{
				cmd = add_list_cmd(cmd);
				cmd->line = ft_strdup(path->cmds);
				parse_list_command(cmd, cmd->line);
				ft_strdel(&path->cmds);
				sort(cmd);
				variables(cmd, path);
				print(cmd);
				check_scommand(cmd);
				commande_effect(cmd, path);
				free_lcommand(&cmd);
			}
			if (var_glob == 111 && line[0] != '\n')
				ft_putendl_fd("", 1);
			bash_promp();
			var_glob = 11;
		}
		frees(&line);
	}
}