#include "minishell.h"

t_list_cmd *add_list_cmd(t_list_cmd *parent)
{
    t_list_cmd *tmp;
    t_list_cmd *new;

    if (parent == NULL)
    {
        if (!(parent = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
            return (NULL);
        if (!(parent->command = (t_command *)malloc(sizeof(t_command))))
            return (NULL);
        if (!(parent->command->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
            return (NULL);
        parent->command->s_left->l_element = NULL;
        parent->command->s_left->right = NULL;
        parent->command->right = NULL;
        ft_bzero(&parent->command->tool, sizeof(t_tool));
        parent->next = NULL;
        parent->previous = NULL;
        return (parent);
    }
    tmp = parent;
    if (!(new = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
        return (NULL);
    if (!(new->command = (t_command *)malloc(sizeof(t_command))))
        return (NULL);
    if (!(new->command->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    new->next = NULL;
    new->previous = NULL;
    new->command->right = NULL;
    ft_bzero(&new->command->tool, sizeof(t_tool));
    new->command->s_left->l_element = NULL;
    new->command->s_left->right = NULL;

    while (tmp->next != NULL)
        tmp = tmp->next;
    new->previous = tmp;
    tmp->next = new;
    return (parent);
}

t_command *add_command(t_command *parent)
{
    t_command *tmp;
    t_command *new;

    if (parent == NULL)
    {
        if (!(parent = (t_command *)malloc(sizeof(t_command))))
            return (NULL);
        if (!(parent->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
            return (NULL);
        // bzero(parent, sizeof(t_command));
        parent->s_left->l_element = NULL;
        parent->s_left->right = NULL;
        parent->right = NULL;
        ft_bzero(&parent->tool, sizeof(t_tool));
        return (parent);
    }

    tmp = parent;
    if (!(new = (t_command *)malloc(sizeof(t_command))))
        return (NULL);
    if (!(new->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    new->right = NULL;
    ft_bzero(&new->tool, sizeof(t_tool));
    new->s_left->l_element = NULL;
    new->s_left->right = NULL;
    while (tmp->right != NULL)
        tmp = tmp->right;
    tmp->right = new;
    return (parent);
}

t_command *add_simple_cmd(t_command *parent, int i)
{
    t_simple_command *tmp;
    t_simple_command *new;
    if (parent->s_left->l_element == NULL)
    {
        // if (!(parent->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
        //     return (NULL);
        if (!(parent->s_left->l_element = (t_elements *)malloc(sizeof(t_elements))))
            return (NULL);
        parent->s_left->l_element->cmd = NULL;
        parent->s_left->l_element->argument = NULL;
        parent->s_left->l_element->redirection.file = NULL;
        parent->s_left->l_element->redirection.i_o = NULL;
        parent->s_left->l_element->indice = i;
        parent->s_left->right = NULL;
        parent->s_left->parent = NULL;
        return (parent);
    }
    tmp = parent->s_left;
    if (!(new = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    if (!(new->l_element = (t_elements *)malloc(sizeof(t_elements))))
        return (NULL);
    new->l_element->indice = i;
    new->right = NULL;
    new->parent = NULL;
    while (parent->s_left->right != NULL)
        parent->s_left = parent->s_left->right;
    new->parent = parent->s_left;
    parent->s_left->right = new;
    return (parent);
}

char *alloc_command(char *line, int i, int *save)
{
    char *command;
    int p;

    p = 0;
    if (!(command = (char *)malloc(sizeof(char) * (i - *save))))
        return (NULL);
    while (*save < i)
    {
        command[p++] = line[(*save)++];
    }
    // khasni nmodifi hadshi man ba3d
    command[p] = '\0';
    *save = i + 1;
    return (command);
}

void alloc_affect(t_list_cmd *l_cmd, char *command, int indice)
{

    if (indice == 1)
    {
        l_cmd->command->tool.cmd = 1;
        l_cmd->command = add_simple_cmd(l_cmd->command, 1);
        if (l_cmd->command->s_left->right != NULL)
            l_cmd->command->s_left = l_cmd->command->s_left->right;
        l_cmd->command->s_left->l_element->cmd = ft_strdup(command);
    }
    else if (indice == 2)
    {
        l_cmd->command->tool.argument = 2;
        l_cmd->command = add_simple_cmd(l_cmd->command, 2);
        if (l_cmd->command->s_left->right != NULL)
            l_cmd->command->s_left = l_cmd->command->s_left->right;
        l_cmd->command->s_left->l_element->argument = ft_strdup(command);
    }
    else if (indice == 3)
    {
        l_cmd->command->tool.argument = 3;
        l_cmd->command = add_simple_cmd(l_cmd->command, 3);
        if (l_cmd->command->s_left->right != NULL)
            l_cmd->command->s_left = l_cmd->command->s_left->right;
        l_cmd->command->s_left->l_element->redirection.file = ft_strdup(command);
        if (wich_redirection(l_cmd->command->tool.check_io) == 2)
            l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup(">>");
        else if (wich_redirection(l_cmd->command->tool.check_io) == 1)
            l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup(">");
        else if (wich_redirection(l_cmd->command->tool.check_io) == 3)
            l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup("<");
    }
}
