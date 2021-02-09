#include "minishell.h"

int get_file_desc(char *file, char *shift)
{
    int fd;

    fd = 0;
    if (!ft_strcmp(">>", shift))
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, FLAG);
    else if (!ft_strcmp(">", shift))
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, FLAG);
    return (fd);
}

int double_red(char *file1, char *file2, char *shift)
{
    int in, out;

    in = open(file2, O_RDONLY);
    out = get_file_desc(file1, shift);
    dup2(in, 0);
    dup2(out, 1);
    close(in);
    close(out);
    return (0);
}

void duping_file(int fd, t_command *cmd, char *file)
{
    if (dup2(fd, 1) < 0)
    {
        ft_putstr_fd(file, 2);
        ft_putendl_fd(": No such file or directory", 2);
        exit(EXIT_FAILURE);
    }
    if (!ft_strcmp(cmd->s_left->l_element->cmd, "exit"))
    {
        ft_putendl_fd("exit", 2);
        kill(0, SIGPIPE);
    }
}

static void opening_files(char *file, char *shifts, t_command *cmd)
{
    int fd;

    if (!ft_strcmp(">>", shifts))
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, FLAG);
    else if (!ft_strcmp(shifts, ">"))
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, FLAG);
    if (!ft_strcmp(shifts, "<"))
    {
        fd = open(file, O_RDONLY, FLAG);
        if (dup2(fd, 0) < 0)
        {
            ft_putstr_fd(file, 2);
            ft_putendl_fd(": No such file or directory", 2);
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
    else
        duping_file(fd, cmd, file);
}

void shift_extra(char *file, char *shifts, t_path *path, t_command *cmd)
{
    int file_desc;
    int status;

    int pid = fork();
    if (pid == 0)
    {
        // if ((get_file_shift(cmd, ">") || get_file_shift(cmd, ">>")) && (get_file_shift(cmd, "<")))
        //     double_red(get_file_shift(cmd, ">") ? get_file_shift(cmd, ">") : get_file_shift(cmd, ">>"),
        //                get_file_shift(cmd, "<"), shifts);
        // else
        //     opening_files(file, shifts, cmd);
        // if (cmdcheck(cmd->s_left->l_element->cmd))
        //     commandes(cmd->s_left->l_element->cmd, path, cmd);
        // else if (cmd->s_left->l_element->cmd)
        //     getprogramme(path, cmd);
        exit(EXIT_SUCCESS);
    }
    wait(&status);
    if (status && !path->dollar)
        _status_cmd(status, path);
}