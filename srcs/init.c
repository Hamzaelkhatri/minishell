#include "../includes/minishell.h"

void init(t_path *path,t_key *key,t_cmd *cmd)
{
    path= malloc(sizeof(t_path));
    ft_bzero(key,sizeof(t_key));
    ft_bzero(cmd,sizeof(t_cmd));
    key->cntrd=0;
    cmd->cd = 0;
    cmd->echo = 0;
    cmd->env = 0;
    cmd->exit = 0;
    cmd->export = 0;
    cmd->pwd = 0;
    cmd->unset = 0;
}