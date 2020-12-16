
#include "minishell.h"

void	unset_cmd(char *name, t_path *path)
{
	int i = 0;
	char **spl;
	int check = 0;
	while (path->env->fullenv[i])
	{
		spl = ft_split(path->env->fullenv[i], '=');
		if ((ft_strlen(spl[0]) == 1) && spl[0][0] == '_')
			break ;
		if (search_str(spl[0], name,ft_strlen(spl[0]), ft_strlen(name)) == 1)
		{
			check++;
		}
		if (check)
			path->env->fullenv[i] = path->env->fullenv[i+1];
		i++;
	}

	path->env->fullenv[i+1] = NULL;
}