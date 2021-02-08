#include "minishell.h"

char *word_tolower(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = ft_tolower(str[i]);
        i++;
    }
    return (str);
}

void free_cmd(int index, char **cmd)
{
    if (index == 2 && cmd)
    {
        free(*cmd);
        *cmd = NULL;
    }
}

int ft_check_str(char *cmd, char *des)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] != ft_tolower(des[i]))
            return (0);
        i++;
    }
    return (1);
}

void commandes(char *cmd, t_path *path, t_command *l_cmd)
{
    int i = 0;
    char **tmp;
    t_simple_command *cmds;

        cmds = l_cmd->s_left;
    if (!ft_check_str("exit", cmd)) /// TODO : RED LBALL
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
        tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_export(tmp);
        // free_tab(&tmp);
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
    else if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "echo -n"))
    {
        if (l_cmd->s_left->right && !ft_strcmp(l_cmd->s_left->right->l_element->argument, "-n"))
        {
            l_cmd->s_left->right = l_cmd->s_left->right->right;
            i = 1;
        }
        while (l_cmd->s_left) // echo hello wold;
        {
            if(l_cmd->s_left->right)
            echo(l_cmd->s_left->right->l_element->argument, path);
            l_cmd->s_left = l_cmd->s_left->right;
            // frees(&l_cmd->s_left->right->l_element->argument);
            // if (l_cmd->s_left)
            //     ft_putstr_fd(" ", 1);
        }
            printf("samir\n");
        // while(l_cmd->s_left->parent)
        // l_cmd->s_left->parent=l_cmd->s_left->parent->parent;
        // l_cmd->s_left = cmds;
        // printf("%s\n",l_cmd->s_left->l_element->cmd);
        if (ft_strcmp(cmd, "echo -n") && i != 1)
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
    char *tcmp;

    tcmp = ft_strtrim(cmd, "\n");
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
    else if (cmdcheck(tcmp))
        commandes(tcmp, path, l_cmd);
    else
        getprogramme(path, l_cmd);
    frees(&tcmp);
    return (path->dollar);
}