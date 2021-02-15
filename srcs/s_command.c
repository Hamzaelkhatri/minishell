/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:50:34 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/15 15:47:47 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join(t_simple_command **cmd)
{
	t_simple_command	*tmp;
	t_simple_command	*save;
	char				*tmp1;

	tmp = *cmd;
	if ((*cmd)->right->right != NULL && (*cmd)->right->l_element->indice == 2)
	{
		save = (*cmd)->right->right;
		tmp1 = (*cmd)->l_element->cmd;
		(*cmd)->l_element->cmd = ft_strjoin((*cmd)->l_element->cmd, " -n");
		frees(&tmp1);
		*cmd = (*cmd)->right;
		free_s_command(&(*cmd));
		*cmd = save;
		(*cmd)->parent = tmp;
		tmp->right = *cmd;
		*cmd = tmp;
	}
}

static int	check_n(char *str)
{
	int i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	check_echo(t_simple_command **cmd)
{
	t_simple_command	*tmp;
	t_simple_command	*save;
	int					index;

	tmp = *cmd;
	*cmd = (*cmd)->right;
	index = 0;
	if (*cmd != NULL && (*cmd)->l_element->argument != NULL\
		&& check_n((*cmd)->l_element->argument))
	{
		while ((*cmd)->right != NULL &&
				check_n((*cmd)->right->l_element->argument))
		{
			save = (*cmd)->right;
			free_s_command(&(*cmd));
			*cmd = save;
		}
		index = 1;
		(*cmd)->parent = tmp;
		tmp->right = (*cmd);
	}
	*cmd = tmp;
	if (index == 1)
		join(&(*cmd));
}

void		check_scommand(t_list_cmd *l_cmd)
{
	t_list_cmd			*tmp_l_command;
	t_command			*tmp_command;
	t_simple_command	*tmp_s;
	char				*cmd;

	tmp_l_command = l_cmd;
	tmp_command = l_cmd->command;
	tmp_s = l_cmd->command->s_left;
	while (l_cmd != NULL)
	{
		tmp_command = l_cmd->command;
		tmp_s = l_cmd->command->s_left;
		while (l_cmd->command != NULL)
		{
			cmd = l_cmd->command->s_left->l_element->cmd;
			if (cmd != NULL && (ft_strlen(cmd) == 4 &&\
						(ft_strnstr(cmd, "echo", 4))))
				check_echo(&l_cmd->command->s_left);
			l_cmd->command = l_cmd->command->right;
		}
		l_cmd->command = tmp_command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp_l_command;
}
