#include "../includes/minishell.h"

void init(t_path *path,t_key *key)
{
    path= malloc(sizeof(t_path));
    ft_bzero(key,sizeof(t_key));
    key->cntrd=0;
}