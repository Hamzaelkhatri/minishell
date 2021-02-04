
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

void getprogramme(t_path *path, t_command *cmd)
{
    exeute(path, cmd);
}

int check_paths(char *path)
{
    struct stat sb;

    if (stat(path, &sb) == -1)
        return (127);
    return (0);
}

char **args(char *cmd, t_path *path)
{
    char **split;
    split = ft_split(cmd, ' ');
    return (split);
}

int _status_cmd(int status, t_path *path)
{
    if (WIFEXITED(status))
        path->dollar = WEXITSTATUS(status);
    else
        path->dollar = 0;
    return (path->dollar);
}

int exeute(t_path *path, t_command *cmd)
{
    char *binaryPath;
    pid_t a;
    char *cmds;
    int status;

    binaryPath = get_directory(path, cmd->s_left->l_element->cmd);
    cmds = ft_strjoin_command(cmd->s_left);
    a = fork();
    if (a < 0)
        ft_putendl_fd(strerror(errno), 1);
    if (!a)
    {
        if (binaryPath)
            if (execve(binaryPath, args(cmds, path), path->env->fullenv) != 0)
                ft_putendl_fd(strerror(errno), 1);
        exit(EXIT_SUCCESS);
    }
    wait(&status);
    if (!path->dollar)
        _status_cmd(status, path);
    return (path->dollar);
}
