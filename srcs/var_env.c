#include "minishell.h"

char* get_var_env(t_path *path,char *var)
{
    return (search_env(path->env->fullenv,&var[1]));
}