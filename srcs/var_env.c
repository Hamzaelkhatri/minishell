#include "minishell.h"

void show_export(t_path *path)
{
	int i;
	int j;
	char *temp;
	char **env;

	i = 0;
	j = 0;

	env = path->env->fullenv;

   while(i < count_line(env) - 1)
   {
       j = i + 1;
       while(j < count_line(env) - 1)
       {
           if(strcmp(env[i],env[j]) > 0)
           {
               temp = ft_strdup(env[i]);
               env[i] = ft_strdup(env[j]);
               env[j] = ft_strdup(temp);
           }
           j++;
       }
       i++;
   }
  env[count_line(env) - 1] = NULL;
  show_env(env);
}

char* get_var_env(t_path *path,char *var)
{
    return (search_env(path->env->fullenv,&var[1]));
}
