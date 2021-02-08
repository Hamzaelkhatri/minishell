
#include "minishell.h"

void    unset_cmd(char *name, t_path *path)
{
    int i = 0;
	int j = 0;
    char **spl;
    int check = 0;
	// if(ft_strchr(name,'\n'))
		// name = ft_strtrim(name,"\n");
    while (path->env->fullenv[i])
    {
        spl = ft_split(path->env->fullenv[i], '=');
 
		if(ft_strcmp(path->env->fullenv[i],get_befor_equal(name)))
		{
			j = i;
			while (path->env->fullenv[j])
			{
				path->env->fullenv[j]=path->env->fullenv[j+1];
				j++;
			}
		}
        i++;
    }
    if (j)
        path->env->fullenv[j] = NULL;
}