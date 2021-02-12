/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:50:46 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:50:47 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_cmd(t_list_cmd *l_cmd, int *cmd,\
		t_simple_command **tmp_cmd, t_simple_command **tmp_sc)
{
	while (l_cmd->command->s_left->l_element->indice != 1)
		l_cmd->command->s_left = l_cmd->command->s_left->right;
	while (l_cmd->command->s_left->parent != NULL)
	{
		*tmp_cmd = l_cmd->command->s_left;
		l_cmd->command->s_left = l_cmd->command->s_left->parent;
		if (l_cmd->command->s_left->parent != NULL)
			l_cmd->command->s_left->parent->right =
				l_cmd->command->s_left->right;
		l_cmd->command->s_left->right = (*tmp_cmd)->right;
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left->right->parent = l_cmd->command->s_left;
		(*tmp_cmd)->parent = l_cmd->command->s_left->parent;
		(*tmp_cmd)->right = l_cmd->command->s_left;
		l_cmd->command->s_left->parent = *tmp_cmd;
		l_cmd->command->s_left = *tmp_cmd;
		*tmp_sc = l_cmd->command->s_left;
	}
	*cmd = 1;
}

static void	sort_argument(t_list_cmd *l_cmd, t_simple_command **tmp_cmd)
{
	while (l_cmd->command->s_left->parent->l_element->indice != 1 &&
			l_cmd->command->s_left->parent->l_element->indice != 2)
	{
		*tmp_cmd = l_cmd->command->s_left;
		l_cmd->command->s_left = l_cmd->command->s_left->parent;
		if (l_cmd->command->s_left->parent != NULL)
			l_cmd->command->s_left->parent->right =
				l_cmd->command->s_left->right;
		l_cmd->command->s_left->right = (*tmp_cmd)->right;
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left->right->parent = l_cmd->command->s_left;
		(*tmp_cmd)->parent = l_cmd->command->s_left->parent;
		(*tmp_cmd)->right = l_cmd->command->s_left;
		l_cmd->command->s_left->parent = *tmp_cmd;
		l_cmd->command->s_left = *tmp_cmd;
	}
}

void		boucle(t_list_cmd *l_cmd, t_tmp *tmp)
{
	int	cmd;

	cmd = 0;
	while (l_cmd->command != NULL)
	{
		tmp->sc = l_cmd->command->s_left;
		cmd = 0;
		while (l_cmd->command->s_left != NULL)
		{
			if (cmd == 0 && l_cmd->command->tool.cmd == 1 &&
					l_cmd->command->s_left->l_element->indice == 1)
				sort_cmd(l_cmd, &cmd, &tmp->cmd, &tmp->sc);
			else if (l_cmd->command->s_left->l_element->indice == 2)
			{
				while (l_cmd->command->s_left->parent->l_element->indice != 1\
					&& l_cmd->command->s_left->parent->l_element->indice != 2)
					sort_argument(l_cmd, &tmp->cmd);
			}
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		}
		l_cmd->command->s_left = tmp->sc;
		l_cmd->command = l_cmd->command->right;
	}
}

void		sort(t_list_cmd *l_cmd)
{
	t_tmp tmp;

	tmp.lc = l_cmd;
	tmp.command = l_cmd->command;
	tmp.sc = l_cmd->command->s_left;
	while (l_cmd != NULL)
	{
		tmp.command = l_cmd->command;
		tmp.sc = l_cmd->command->s_left;
		boucle(l_cmd, &tmp);
		l_cmd->command = tmp.command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp.lc;
}
