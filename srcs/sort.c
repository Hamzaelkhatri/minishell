#include "minishell.h"

void sort(t_list_cmd *l_cmd)
{
    t_list_cmd *tmp_lc;
    t_command *tmp_command;
    t_simple_command *tmp_sc;
    t_simple_command *tmp_cmd;
    t_simple_command *tmp_cmd_parent;

    int i = 0;
    int cmd;

    tmp_lc = l_cmd;
    tmp_command = l_cmd->command;
    tmp_sc = l_cmd->command->s_left;
    while (l_cmd != NULL)
    {
        tmp_command = l_cmd->command;
        tmp_sc = l_cmd->command->s_left;
        cmd = 0;
        while (l_cmd->command != NULL)
        {
            tmp_sc = l_cmd->command->s_left;
            while (l_cmd->command->s_left != NULL)
            {
                if (cmd == 0 && l_cmd->command->tool.cmd == 1 && l_cmd->command->s_left->l_element->indice == 1)
                {

                    while (l_cmd->command->s_left->l_element->indice != 1)
                        l_cmd->command->s_left = l_cmd->command->s_left->right;
                    while (l_cmd->command->s_left->parent != NULL)
                    {
                        tmp_cmd = l_cmd->command->s_left;
                        l_cmd->command->s_left = l_cmd->command->s_left->parent;
                        if (l_cmd->command->s_left->parent != NULL)
                            l_cmd->command->s_left->parent->right = l_cmd->command->s_left->right;
                        l_cmd->command->s_left->right = tmp_cmd->right;
                        if (l_cmd->command->s_left->right != NULL)
                            l_cmd->command->s_left->right->parent = l_cmd->command->s_left;
                        tmp_cmd->parent = l_cmd->command->s_left->parent;
                        tmp_cmd->right = l_cmd->command->s_left;
                        l_cmd->command->s_left->parent = tmp_cmd;
                        l_cmd->command->s_left = tmp_cmd;
                        tmp_sc = l_cmd->command->s_left;
                    }
                    cmd = 1;
                }
                else if (l_cmd->command->s_left->l_element->indice == 2)
                {
                    while (l_cmd->command->s_left->parent->l_element->indice != 1 && l_cmd->command->s_left->parent->l_element->indice != 2)
                    {
                        tmp_cmd = l_cmd->command->s_left;
                        l_cmd->command->s_left = l_cmd->command->s_left->parent;
                        if (l_cmd->command->s_left->parent != NULL)
                            l_cmd->command->s_left->parent->right = l_cmd->command->s_left->right;
                        l_cmd->command->s_left->right = tmp_cmd->right;
                        if (l_cmd->command->s_left->right != NULL)
                            l_cmd->command->s_left->right->parent = l_cmd->command->s_left;
                        tmp_cmd->parent = l_cmd->command->s_left->parent;
                        tmp_cmd->right = l_cmd->command->s_left;
                        l_cmd->command->s_left->parent = tmp_cmd;
                        l_cmd->command->s_left = tmp_cmd;
                    }
                }
                l_cmd->command->s_left = l_cmd->command->s_left->right;
            }
            l_cmd->command->s_left = tmp_sc;
            l_cmd->command = l_cmd->command->right;
        }
        // l_cmd->command->s_left = tmp_sc;
        l_cmd->command = tmp_command;
        l_cmd = l_cmd->next;
    }
    l_cmd = tmp_lc;
}

// l_cmd->s_left->parent->right = l_cmd->s_left->right;
// if (l_cmd->s_left->right != NULL)
//     l_cmd->s_left->right->parent = l_cmd->s_left->parent;
// l_cmd->s_left->right = l_cmd->s_left->parent;
// l_cmd->s_left->parent = tmp->parent;
// tmp->parent = l_cmd->s_left;
