#include "minishell.h"

void	export_cmd(char *name,char **env)
{
	int i = 0;
	int line = count_line(env);
	env[line] = name;
	env[line+1] = NULL;
}
