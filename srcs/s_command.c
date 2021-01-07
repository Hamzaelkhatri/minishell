#include "minishell.h"

static void	check_echo(t_simple_command **cmd)
{
	t_simple_command *tmp;
	t_simple_command *save;

	tmp = *cmd;
	*cmd = (*cmd)->right;
	if (*cmd != NULL && ft_str_in_str((*cmd)->l_element->argument, "-n"))
	{
		while ((*cmd)->right != NULL &&\
			ft_str_in_str((*cmd)->right->l_element->argument, "-n"))
		{
			save = (*cmd)->right;
			free_s_command(&(*cmd));
			*cmd = save;
		}
		(*cmd)->parent = tmp;
		tmp->right = (*cmd);
	}
	*cmd = tmp;
}

void		check_scommand(t_list_cmd *l_cmd)
{
	t_list_cmd			*tmp_l_command;
	t_command			*tmp_command;
	t_simple_command	*tmp_s;

	tmp_l_command = l_cmd;
	tmp_command = l_cmd->command;
	tmp_s = l_cmd->command->s_left;
	while (l_cmd != NULL)
	{
		tmp_command = l_cmd->command;
		tmp_s = l_cmd->command->s_left;
		while (l_cmd->command != NULL)
		{
			if (ft_str_in_str(l_cmd->command->s_left->l_element->cmd, "echo"))
				check_echo(&l_cmd->command->s_left);
			l_cmd->command = l_cmd->command->right;
		}
		l_cmd->command = tmp_command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp_l_command;
}
