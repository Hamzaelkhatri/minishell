
#include "minishell.h"

void	unset_cmd(char *name, t_path *path)
{
	int i = 0;
	if(search_env(path->env->fullenv,name))
	{
		while (path->env->fullenv[i])
		{
			path->env->fullenv[i] = path->env->fullenv[i+1];
			i++;
		}
		path->env->fullenv[i+1] = NULL;
	}
}