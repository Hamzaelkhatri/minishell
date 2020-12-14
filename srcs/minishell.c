#include "../includes/minishell.h"


int count_line(char **env)
{
	int i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

void	export_cmd(char *name,char **env)
{
	int i = 0;
	int line = count_line(env);
	printf("{%d}",line);
	env[line] = name;
	env[line+1] = NULL;
}

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	// char *env_tmp[33];
	char *s;
	init(&path,&key,&cmd);
	path.env->fullenv = env;
	get_directory(&path);
	loop_shell(&cmd,&path);
	getprogramme(&path,"pwd");
	return (0);
}