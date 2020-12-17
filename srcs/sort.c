#include "minishell.h"

void sort(t_list_cmd *l_cmd)
{
    t_list_cmd *tmp_lc;
    t_simple_command *tmp_sc;

    tmp_lc = l_cmd;
    tmp_sc = l_cmd->s_left;
    // while (l_cmd != NULL)
    // {
    while (l_cmd->s_left != NULL)
    {
        if (l_cmd->s_left->parent == NULL)
            ft_putstr_fd("fen a sahbi\n", 1);
        l_cmd->s_left = l_cmd->s_left->right;
    }
    // l_cmd = l_cmd->right;
    // }
    l_cmd->s_left = tmp_sc;
}