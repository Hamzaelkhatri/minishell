#include "minishell.h"

void print(t_list_cmd *l_command)
{
    t_list_cmd *tmp_l_command;
    t_command *tmp_command;
    t_simple_command *tmp_s;

    tmp_l_command = l_command;
    tmp_command = l_command->command;
    tmp_s = l_command->command->s_left;
    while (l_command != NULL)
    {
        tmp_command = l_command->command;
        tmp_s = l_command->command->s_left;
        while (l_command->command != NULL)
        {
            tmp_s = l_command->command->s_left;
            while (l_command->command->s_left != NULL)
            {
                if (l_command->command->s_left->l_element->indice == 1)
                    printf("|cmd  ==> %s|\n", l_command->command->s_left->l_element->cmd);
                else if (l_command->command->s_left->l_element->indice == 2)
                    printf("|argument  ==> %s|\n", l_command->command->s_left->l_element->argument);
                else if (l_command->command->s_left->l_element->indice == 3)
                    printf("|direction ==> %s|\t|redirection ==> %s|\n", l_command->command->s_left->l_element->redirection.i_o, l_command->command->s_left->l_element->redirection.file);
                l_command->command->s_left = l_command->command->s_left->right;
            }
            l_command->command->s_left = tmp_s;
            l_command->command = l_command->command->right;
        }
        // ft_putendl_fd("--------- command2 ----------", 1);
        if (l_command->next != NULL)
            ft_putendl_fd("--------- list ----------", 1);
        l_command->command = tmp_command;
        l_command = l_command->next;
    }
    // l_command->command->s_left = tmp_s;
    l_command = tmp_l_command;

    // l_command = tmp;
}

//|ls -la ;     V
//ls "| ls"     V
//echo "\"a"    V
// echo a | "d" V
// echo -nnn -n -n a
// echo -nann -n -n a
// cat < a >    V
// cat >        V
// cat ">" (argument not redirection)
// >echo
