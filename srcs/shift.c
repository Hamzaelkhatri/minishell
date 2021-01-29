#include "minishell.h"

void shift_extra(char *file, char *shifts, t_path *path, t_command *cmd)
{
    int file_desc;
    char *cmds;

    int pid = fork();
    if (pid == 0)
    {
        if (!ft_strcmp(">>", shifts))
            file_desc = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
        else if (!ft_strcmp(shifts, ">"))
            file_desc = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (!ft_strcmp(shifts, "<"))
        {
            file_desc = open(file, O_RDONLY);
            if (dup2(file_desc, 0) < 0)
            {
                
                ft_putstr_fd(file, 2);
                ft_putendl_fd(": No such file or directory", 2);
                exit(EXIT_FAILURE);
            }
            close(file_desc);
        }
        else
        {
            if (dup2(file_desc, 1) < 0)
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
            if (!cmd->s_left->l_element->cmd)
                ft_putstr_fd("", 1);
        }
        if (cmdcheck(cmd->s_left->l_element->cmd))
            commandes(cmd->s_left->l_element->cmd, path, cmd);
        else if (cmd->s_left->l_element->cmd)
        {
            cmds = ft_strjoin_command(cmd->s_left);
            getprogramme(path, cmd->s_left->l_element->cmd);
        }
        exit(EXIT_SUCCESS);
    }
    wait(0);
}