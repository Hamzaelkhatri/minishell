#include "minishell.h"

void cd_cmd(char *nextPath, t_path *path)
{
    char *tmp;

    path->dollar = 0;
    if (nextPath == NULL)
        nextPath = search_env(path->env->fullenv, "HOME");
    tmp = getcwd(NULL, 100);
    edit_env(path->env->fullenv, "OLDPWD", tmp);
    frees(&tmp);
    if (strchr(nextPath, '\n'))
        nextPath = ft_strtrim(nextPath, "\n");
    if (chdir(nextPath))
    {
        ft_putstr_fd("\e[1;31mbash :", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(" ", 2);
        ft_putendl_fd(nextPath, 2);
        path->dollar = 1;
    }
    tmp = getcwd(NULL, 100);
    edit_env(path->env->fullenv, "PWD", tmp);
    frees(&tmp);
}
