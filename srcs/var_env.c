#include "minishell.h"

char* get_var_env(t_path *path,char *var)
{
    return (search_env(path->env->fullenv,&var[1]));
}

char *search_env1(char **env, char *str)
{
	int i;
	int j;
	char *tmp;
	char *soso;

	j = ft_strlen(str) + 1;
	i = 0;
	while (env[i])
	{
		soso = get_befor_equal(env[i]);
		if (strcmp(soso, str) == 0)
		{
			tmp = ft_str_to_equal(env[i], str, ft_strlen(str));
			free(soso);
			return &tmp[j];
		}
		free(soso);
		i++;
	}
	return (NULL);
}

char *get_var_env1(t_path *path, char *var)
{
	return (search_env1(path->env->fullenv, &var[1]));
}