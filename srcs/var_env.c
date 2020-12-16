#include "minishell.h"

void get_var_env(t_path *path,char *var)
{
    printf("%s",search_env(path->env->fullenv,&var[1]));
    // if()
}