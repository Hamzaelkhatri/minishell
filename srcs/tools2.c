#include "minishell.h"

void	quotes_extended(t_list_cmd *l_cmd, t_simple_command *tmp_s)
{
	while (l_cmd->command != NULL)
	{
		tmp_s = l_cmd->command->s_left;
		while (l_cmd->command->s_left != NULL)
		{
			if (l_cmd->command->s_left->l_element->indice == 1)
				l_cmd->command->s_left->l_element->cmd =\
				ignoring_quote(l_cmd->command->s_left->l_element->cmd);
			else if (l_cmd->command->s_left->l_element->indice == 2)
				l_cmd->command->s_left->l_element->argument =\
				ignoring_quote(l_cmd->command->s_left->l_element->argument);
			else if (l_cmd->command->s_left->l_element->indice == 3)
				l_cmd->command->s_left->l_element->redirection.file =\
				ignoring_quote(l_cmd->command->s_left->l_element->\
						redirection.file);
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		}
		l_cmd->command->s_left = tmp_s;
		l_cmd->command = l_cmd->command->right;
	}
}

void	quotes(t_list_cmd *l_cmd)
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
		quotes_extended(l_cmd, tmp_s);
		l_cmd->command = tmp_command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp_l_command;
}

void	alloc_affect_extended(t_list_cmd **l_cmd, char *command, int indice, t_save *save)
{
	(*l_cmd)->command->tool.redirection = 1;
	(*l_cmd)->command = add_simple_cmd((*l_cmd)->command, 3, (*l_cmd));
	if ((*l_cmd)->command->s_left->right != NULL)
		(*l_cmd)->command->s_left = (*l_cmd)->command->s_left->right;
	(*l_cmd)->command->s_left->l_element->redirection.file = ft_strdup(command);
	// frees(&save->file);
		(*l_cmd)->command->s_left->l_element->redirection.i_o = ft_strdup(save->red);
	// frees(&save->red);
}

void	alloc_affect(t_list_cmd *l_cmd, char *command, int indice, t_save *save)
{
	if (indice == 1)
	{
		l_cmd->command->tool.cmd = 1;
		l_cmd->command = add_simple_cmd(l_cmd->command, 1, l_cmd);
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		l_cmd->command->s_left->l_element->cmd = ft_strdup(command);
	}
	else if (indice == 2)
	{
		l_cmd->command->tool.argument = 1;
		l_cmd->command = add_simple_cmd(l_cmd->command, 2, l_cmd);
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		l_cmd->command->s_left->l_element->argument = ft_strdup(command);
	}
	else if (indice == 3)
		alloc_affect_extended(&l_cmd, command, indice, save);
}

int		ft_2strlen(char **str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}
