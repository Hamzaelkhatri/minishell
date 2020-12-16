#include "minishell.h"

int cd_cmd(char *nextPath,t_path *path)
{
    char *s;
    getcwd(path->env->oldpwd,100);
    if(chdir(nextPath))
    {
        perror("bash$ ");
        return (0);
    }
    getcwd(s,100);
    path->env->pwd = ft_strdup(s);
    return (1);
}