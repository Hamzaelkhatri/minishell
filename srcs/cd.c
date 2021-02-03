#include "minishell.h"

void cd_cmd(char *nextPath, t_path *path)
{
    char *s;
    char *s1;

    path->dollar = 0;
    if (nextPath == NULL)
        nextPath = search_env(path->env->fullenv, "HOME");
    if (!ft_strncmp(nextPath, "$", 1) && get_var_env(path, nextPath))
        nextPath = ft_strdup(get_var_env(path, nextPath));
    edit_env(path->env->fullenv, "OLDPWD", getcwd(NULL, 100));
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
    edit_env(path->env->fullenv, "PWD", getcwd(NULL, 100));
}
