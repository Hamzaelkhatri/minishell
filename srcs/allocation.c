#include "minishell.h"

t_list_cmd *add_list_cmd(t_list_cmd *parent)
{
    t_list_cmd *tmp;
    t_list_cmd *new;

    if (parent == NULL)
    {
        if (!(parent = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
            return (NULL);
        // bzero(parent, sizeof(t_list_cmd));
        parent->s_left = NULL;
        parent->right = NULL;
        return (parent);
    }
    tmp = parent;
    if (!(new = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
        return (NULL);
    new->right = NULL;
    new->s_left = NULL;
    while (tmp->right != NULL)
        tmp = tmp->right;
    tmp->right = new;
    return (parent);
}

t_list_cmd *add_simple_cmd(t_list_cmd *parent)
{
    t_simple_command *tmp;
    t_simple_command *new;
    static int i = 0;
    if (parent->s_left == NULL)
    {
        if (!(parent->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
            return (NULL);
        if (!(parent->s_left->l_element = (t_elements *)malloc(sizeof(t_elements))))
            return (NULL);
        parent->s_left->right = NULL;
        return (parent);
    }
    tmp = parent->s_left;
    if (!(new = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    if (!(new->l_element = (t_elements *)malloc(sizeof(t_elements))))
        return (NULL);
    new->right = NULL;
    while (tmp->right != NULL)
        tmp = tmp->right;
    tmp->right = new;
    return (parent);
}
