#include "minishell.h"

int check_link(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/')
            return (127);
        i++;
    }
    return (0);
}

int bash_err(char *cmd)
{
    ft_putstr_fd("\e[1;31mbash: ", 2);
    ft_putstr_fd("no such file or directory: ", 2);
    ft_putendl_fd(cmd, 2);
    return (127);
}

char *get_directory(t_path *path, char *cmd)
{
    char *tmp;
    char *link;
    char **paths;
    int i;

    i = 0;
    tmp = search_env(path->env->fullenv, "PATH");
    if (tmp && !check_link((cmd)))
    {
        paths = ft_split(tmp, ':');
        while (paths[i])
        {
            link = ft_strjoin(paths[i], "/");
            link = ft_strjoin(link, (cmd));
            if (!(path->dollar = check_paths(link)))
                return (link);
            if (link)
                free(link);
            i++;
        }
        path->dollar = bash_err(cmd);
    }
    else if (check_link((cmd)))
    {
        if (!(path->dollar = check_paths((cmd))))
            return ((cmd));
        path->dollar = bash_err(cmd);
    }
    else
    {
        link = ft_strjoin(getcwd(NULL, 100), "/");
        link = ft_strjoin(link, (cmd));
        if (!(path->dollar = !check_paths(link)))
            return (link);
        else
            path->dollar = bash_err(cmd);
    }
    return (NULL);
}