#include "minishell.h"
#include <setjmp.h>
int var_glob = 0;
/* hadi zadtha ha9ash fach kanktab shi haja o kandir ctrl + d o n annuli dakshi li ktabt b ctrl + c 
		     makat3awdsh tkhdam ctrl + d*/

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

void avoid_cntc()
{
	int a;

	a = fork();
	if (!a)
	{
		char *cmd[] = {"/bin/stty", 0};
		char *cmd_args[] = {"stty", "-echoctl", 0};
		char *env[] = {" ", "env", 0};
		execve(cmd[0], cmd_args, env);
		exit(0);
	}
	wait(0);
}

void sigint_handler(int sig)
{
	int a;

	if (sig == SIGINT)
	{
		// var_glob = 100;
		if (var_glob)
			ft_putstr_fd("\n\e[1;32mbash$ \e[0;37m", 2);
		var_glob = 111;
		avoid_cntc();
	}
	if (sig == SIGQUIT)
	{
		var_glob =  111;
	}
}

void promp_bash(t_path *path, int ret, char **line)
{
	if (var_glob == 1)
		path->key->cntrd = 0;
	if (ret == 0 && path->key->cntrd != 1)
	{
		ft_putstr_fd("exit", 1);
		exit(1);
	}
	if (ft_strrchr(*line, '\n'))
	{
		bash_promp();
		path->key->cntrd = 0;
	}
	else if (ft_strrchr(*line, '\n'))
	{
		bash_promp();
		path->key->cntrd = 0;
	}
	if (ret > 0 && !ft_strrchr(*line, '\n'))
		path->key->cntrd = 1;
}
void bash_promp()
{
	ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 2);
}

void loop_shell(t_path *path)
{
	char *line;
	int ret;
	int status;
	int salam;
	t_list_cmd *cmd = NULL;
	struct stat buff;
	int i;
	int check;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cnrtl-C", 2);
	if (signal(SIGQUIT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cntrl-\\", 2);
	status = 0;
	var_glob = 0;
	path->dollar = 0;
	i = 0;
	bash_promp();
	while (!status)
	{
		check = -1;
		i = 0;
		ret = 0;
		ret = read_line(path, &line);
		if (line[0] == '\0')
		{
			ft_putendl_fd("exit", 1);
			exit(EXIT_SUCCESS);
		}
		else if (line[0] == '\n')
			check = 0;
		path->cmds = line;
		if (check != 0)
			while (line[i] && line[i] == ' ')
				i++;
		if (line[i] != '\n')
		{
			path->cmds = ft_strtrim(path->cmds, "\n");
			check = ft_check_line(path->cmds);
		}
		if (check == 1)
		{
			var_glob = 0;
			cmd = add_list_cmd(cmd);
			cmd->line = ft_strdup(path->cmds);
			parse_list_command(cmd, cmd->line);
			ft_strdel(&path->cmds);
			sort(cmd);
			quotes(cmd);
			check_scommand(cmd);
			commande_effect(cmd, path);
			free_lcommand(&cmd);
		}
		if (var_glob == 111 && line[0] != '\n')
			ft_putendl_fd("", 1);
		bash_promp();
		var_glob = 11;
	}
}