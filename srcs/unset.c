
#include "minishell.h"

void unset_cmd(char *name, t_path *path)
{
	int i = 0;
	char **spl;
	int check = 0;
	name = ft_strtrim(name, "\n");
	int k = count_line(path->env->fullenv);
	while (i < k)
	{
		spl = ft_split(path->env->fullenv[i], '=');
		if (ft_strcmp(spl[0],"_"))
		{
			if (!ft_strcmp(spl[0], name))
				check++;
			if (check)
				path->env->fullenv[i] = path->env->fullenv[i + 1];
		}
		i++;
	}
	if (!check)
		path->env->fullenv[k] = NULL;
	else
		path->env->fullenv[k - 1] = NULL;
}