#include "minishell.h"

int commande_effect(t_list_cmd *lst,t_path *path)
{
    while (lst)
    {
        if(lstsize(lst)>1)
        {
            pipes_cmd(path,lst);
        }
        else
        {
            printf("simple");
        }
        // printf("1");
        lst = lst->next;
    }
    return 0;
}