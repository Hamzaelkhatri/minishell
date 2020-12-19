#include "minishell.h"

t_list_cmd *add_list_cmd(t_list_cmd *parent)
{
    t_list_cmd *tmp;
    t_list_cmd *new;

    if (parent == NULL)
    {
        if (!(parent = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
            return (NULL);
        if (!(parent->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
            return (NULL);
        // bzero(parent, sizeof(t_list_cmd));
        parent->s_left->l_element = NULL;
        parent->s_left->right = NULL;
        parent->right = NULL;
        ft_bzero(&parent->tool, sizeof(t_tool));
        return (parent);
    }
    tmp = parent;
    if (!(new = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
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

t_list_cmd *add_simple_cmd(t_list_cmd *parent, int i)
{
    t_simple_command *tmp;
    t_simple_command *new;
    if (parent->s_left->l_element == NULL)
    {
        // if (!(parent->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
        //     return (NULL);
        if (!(parent->s_left->l_element = (t_elements *)malloc(sizeof(t_elements))))
            return (NULL);
        // parent->s_left->l_element->cmd = NULL;
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
