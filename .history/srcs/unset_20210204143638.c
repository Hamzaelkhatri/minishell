
#include "minishell.h"

void    unset_cmd(char *name, t_path *path)
{
    int i = 0;
	int j = 0;
    char **spl;
    int check = 0;
	if(ft_strchr(name,'\n'))
		name = ft_strtrim(name,"\n");
    while (path->env->fullenv[i])
    {
        spl = ft_split(path->env->fullenv[i], '=');
        if ((ft_strlen(spl[0]) == 1) && spl[0][0] == '_')
            break ;
		if(ft_strnstr(path->env->fullenv[i],name,cout_to_char(path->env->fullenv[i],'=')))
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
        path->env->fullenv[j+1] = NULL;
}