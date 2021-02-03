#include "minishell.h"

char *word_tolower(char *str)
{
    int i;
    char *ptr;

    i = 0;
    ptr = malloc(sizeof(char) * ft_strlen(str));
    while (str[i])
    {
        ptr[i] = ft_tolower(str[i]);
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}

void commandes(char *cmd, t_path *path, t_command *l_cmd)
{
    // puts(cmd);
    if (!ft_strcmp("exit", word_tolower(cmd)))
        cmd = word_tolower(cmd);
    if (!ft_strcmp(cmd, "pwd"))
    {
        print_working_directory(path);
        path->dollar = 0;
    }
    else if (!ft_strcmp(cmd, "env"))
    {
        show_env(path->env->fullenv);
        path->dollar = 0;
    }
    else if (!ft_strcmp(cmd, "cd"))
    {
        if (l_cmd->s_left->right != NULL)
            cd_cmd(l_cmd->s_left->right->l_element->argument, path);
        else
            cd_cmd(NULL, path);
    }
    else if (!ft_strcmp(cmd, "exit"))
        exit_exec(l_cmd);
    else if (!ft_strcmp(cmd, "export") && l_cmd->s_left->right == NULL)
    {
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_export(tmp);
        path->dollar = 0;
    }
    else if (!ft_strcmp(cmd, "export") && l_cmd->s_left->right != NULL)
    {
        while (l_cmd->s_left->right)
        {
            if (!export_cmd(l_cmd->s_left->right->l_element->argument, path))
                break;
            l_cmd->s_left->right = l_cmd->s_left->right->right;
        }
    }
    else if (!ft_strcmp(cmd, "unset") && l_cmd->s_left->right != NULL)
    {
        unset_cmd(l_cmd->s_left->right->l_element->argument, path);
        path->dollar = 0;
    }
    else if (!ft_strcmp(cmd, "echo"))
    {
        if (l_cmd->s_left->right)
            if (!ft_strcmp(l_cmd->s_left->right->l_element->argument, "-n\n"))
            {
                cmd = ft_strjoin(cmd, " -n");
                l_cmd->s_left->right = l_cmd->s_left->right->right;
            }
        while (l_cmd->s_left->right)
        {
            echo(l_cmd->s_left->right->l_element->argument, path);
            l_cmd->s_left->right = l_cmd->s_left->right->right;
            if (l_cmd->s_left->right)
                ft_putstr_fd(" ", 1);
        }
        if (ft_strcmp(cmd, "echo -n"))
            ft_putendl_fd("", 1);
        path->dollar = 0;
    }
}

char *get_file_shift(t_command *lcmd, char *shift)
{
    int fd;

    t_simple_command *cmd = lcmd->s_left;
    while (cmd)
    {
        if (cmd->l_element->indice == 3 && !ft_strcmp(cmd->l_element->redirection.i_o, shift) && ft_strcmp("<", shift) && cmd->right == NULL)
            return (cmd->l_element->redirection.file);
        else if (cmd->l_element->indice == 3 && !ft_strcmp(cmd->l_element->redirection.i_o, shift) && !ft_strcmp("<", shift) && ft_strcmp(cmd->right->l_element->redirection.i_o, "<"))
            return (cmd->l_element->redirection.file);
        else if (cmd->l_element->indice == 3 && ft_strcmp(cmd->l_element->redirection.i_o, "<"))
            create_file(cmd->l_element->redirection.file);
        cmd = cmd->right;
    }
    return (NULL);
}

char *get_file(t_command *lcmd)
{
    t_simple_command *cmd = lcmd->s_left;
    while (cmd)
    {
        if (cmd->l_element->indice == 3 && cmd->right == NULL)
            return (cmd->l_element->redirection.file);
        cmd = cmd->right;
    }
    return (NULL);
}

int create_file(char *file)
{
    int fd;
    fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, FLAG);
    ft_putstr_fd("", fd);
    close(fd);
    return (0);
}

char *get_shift(t_command *lcmd)
{
    t_simple_command *cmd;
    int fd;

    cmd = lcmd->s_left;
    while (cmd)
    {
        if (cmd->l_element->indice == 3 && cmd->right == NULL)
        {
            return (cmd->l_element->redirection.i_o);
        }
        else if (cmd->l_element->indice == 3 && ft_strcmp(cmd->l_element->redirection.i_o, "<"))
            create_file(cmd->l_element->redirection.file);
        cmd = cmd->right;
    }
    return (NULL);
}

int get_cmd_(char *cmd, t_path *path, t_command *l_cmd)
{
    char *cmds;
    t_command *tmp;
    t_simple_command *s_tmp = l_cmd->s_left;

    // puts(cmd);
    cmd = ft_strtrim(cmd, "\n");
    if (!ft_strcmp("$?", cmd))
        ft_putnbr_fd(path->dollar, 2);
    if (get_shift(l_cmd))
    {
        tmp = l_cmd;
        shift_extra(get_file(tmp), get_shift(tmp), path, tmp);
    }
    else if (l_cmd->s_left->l_element->redirection.i_o)
        while (l_cmd->s_left)
        {
            if (l_cmd->s_left->l_element->redirection.file)
                shift_extra(l_cmd->s_left->l_element->redirection.file, l_cmd->s_left->l_element->redirection.i_o, path, l_cmd);
            l_cmd->s_left = l_cmd->s_left->right;
        }
    else if (cmdcheck(cmd))
    {
        commandes(cmd, path, l_cmd);
    }
    else
    {
        getprogramme(path, l_cmd);
    }
    wait(0);
    return 0;
}