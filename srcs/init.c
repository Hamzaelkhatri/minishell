#include "minishell.h"

void init(t_path *path, t_key *key, t_cmd *cmd)
{
    ft_bzero(key, sizeof(t_key));
    ft_bzero(cmd, sizeof(t_cmd));
    path->key = malloc(sizeof(t_key));
    path->env = malloc(sizeof(t_env));
    // path.env = env;
    // ft_bzero(path->key,sizeof(t_key));
    // path->key->cntrd=0;
    // cmd->cd = 0;
    // cmd->echo = 0;
    // cmd->env = 0;
    // cmd->exit = 0;
    // cmd->export = 0;
    // cmd->pwd = 0;
    // cmd->unset = 0;
}

void	init_simple_cmd(t_simple_command **parent, int i)
{
	(*parent)->l_element->cmd = NULL;
	(*parent)->l_element->argument = NULL;
	(*parent)->l_element->redirection.file = NULL;
	(*parent)->l_element->redirection.i_o = NULL;
	(*parent)->l_element->indice = i;
	(*parent)->right = NULL;
	(*parent)->parent = NULL;
}

void	init_lcommand(t_list_cmd **parent)
{
	(*parent)->line = NULL;
	(*parent)->command->s_left->l_element = NULL;
	(*parent)->command->s_left->right = NULL;
	(*parent)->command->right = NULL;
	(*parent)->next = NULL;
	(*parent)->previous = NULL;
	ft_bzero(&(*parent)->command->tool, sizeof(t_tool));
}
