#include "minishell.h"

int commande_effect(t_list_cmd *lst,t_path *path)
{
    while (lst)
    {
        if(lstsize(lst)>1)
        {
            pipes_cmd(path,lst);
            wait(0);
        }
        else
        {
            get_cmd_(lst->command->s_left->l_element->cmd,path,lst->command);
        }
        lst = lst->next;
    }
    return 0;
}