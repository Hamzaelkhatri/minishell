#include "minishell.h"

void ft_exit(t_list_cmd *l_cmd,int error)
{
    ft_putendl_fd(strerror(error),2);
    free_lcommand(&l_cmd);
    exit(1);
}