
#include "minishell.h"

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
    return (ft_split(cmd, ' '));
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
    char **tmp;
    char *cmds;
    int status;

    // binaryPath = get_directory(path, cmd->s_left->l_element->cmd);
    // cmds = ft_strjoin_command(cmd->s_left);
    // tmp = args(cmds, path);
    // a = fork();
    // if (a < 0)
    //     ft_putendl_fd(strerror(errno), 1);
    // if (!a)
    // {
    //     if (binaryPath)
    //         if (execve(binaryPath, tmp, path->env->fullenv) != 0)
    //             ft_putendl_fd(strerror(errno), 1);
    //     exit(EXIT_SUCCESS);
    // }
    // wait(&status);
    // if (status && !path->dollar)
    //     _status_cmd(status, path);
    // frees(&binaryPath);
    // free_tab(&tmp);
    // frees(&cmds);
    return (path->dollar);
}
