#include "minishell.h"

void cd_cmd(char *nextPath, t_path *path)
{
    char *s;
    if (!nextPath || !ft_strcmp(nextPath, "~"))
    {
        nextPath = get_var_env(path, "$HOME");;
        if (chdir(nextPath) < 0)
        {
            ft_putendl_fd(strerror(errno), 1);
        }
    }
    else if (nextPath[0] == '$')
    {
        s = get_var_env(path, nextPath);
        if (!s && (chdir(nextPath) < 0))
            ft_putendl_fd(strerror(errno), 1);
        else
        {
            nextPath = get_var_env(path, nextPath);
            if (chdir(nextPath) < 0)
            {
                ft_putendl_fd(strerror(errno), 1);
            }
        }
    }
    else if (chdir(nextPath) < 0)
    {
        ft_putendl_fd(strerror(errno), 1);
    }
}