
#include "minishell.h"

char *strfromto(char *str, int from, char to)
{
    int i;
    char *ret;

    i = from;
    ret = malloc(from * sizeof(char));
    while (str[i] != to)
    {
        ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return (&ret[1]);
}

char *search_prev(char *str, char c, int i)
{
    char *ptr;
    while (i >= 0)
    {
        if (str[i] == c)
            return (strfromto(str, i, '-'));
        i--;
    }
    return (NULL);
}

void getprogramme(t_path *path, char *cmd)
{
    int i;
    exeute(path, cmd);
}

int check_paths(char *path)
{
    struct stat sb;

    if (stat(path, &sb) == -1)
        return (0);
    return (1);
}

char **args(char *cmd,t_path *path)
{
    char **split;
    split = ft_split(cmd, ' ');
    return (split);
}

void exeute(t_path *path, char *cmd)
{
    char *binaryPath;
    pid_t a;

    a = fork();
    if (a < 0)
        ft_putendl_fd(strerror(errno), 1);
    if (!a)
    {
        binaryPath = get_directory(path, cmd);
        if (binaryPath)
            if (execve(binaryPath, args(cmd,path), path->env->fullenv) != 0)
                ft_putendl_fd(strerror(errno), 1);
        exit(a);
    }
    wait(&a);
}
