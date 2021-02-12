/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:49 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:46:52 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	allocation_lcmd(t_list_cmd **new, t_list_cmd **parent)
{
	if (!((*new) = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
		ft_exit(*parent, errno);
	if (!((*new)->command = (t_command *)malloc(sizeof(t_command))))
		ft_exit(*parent, errno);
	if (!((*new)->command->s_left =\
				(t_simple_command *)malloc(sizeof(t_simple_command))))
		ft_exit(*parent, errno);
}

t_list_cmd	*add_list_cmd(t_list_cmd *parent)
{
	t_list_cmd	*tmp;
	t_list_cmd	*new;

	if (parent == NULL)
	{
		allocation_lcmd(&parent, &parent);
		init_lcommand(&parent);
		return (parent);
	}
	tmp = parent;
	allocation_lcmd(&new, &parent);
	init_lcommand(&new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->previous = tmp;
	tmp->next = new;
	return (parent);
}

t_command	*add_command(t_command *parent, t_list_cmd *l_cmd)
{
	t_command	*tmp;
	t_command	*new;

	tmp = parent;
	if (!(new = (t_command *)malloc(sizeof(t_command))))
		ft_exit(l_cmd, errno);
	if (!(new->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
		ft_exit(l_cmd, errno);
	ft_bzero(&new->tool, sizeof(t_tool));
	new->right = NULL;
	new->s_left->l_element = NULL;
	new->s_left->right = NULL;
	while (tmp->right != NULL)
		tmp = tmp->right;
	tmp->right = new;
	return (parent);
}

t_command	*add_simple_cmd(t_command *parent, int i, t_list_cmd *l_cmd)
{
	t_simple_command	*tmp;
	t_simple_command	*new;

	if (parent->s_left->l_element == NULL)
	{
		if (!(parent->s_left->l_element =\
					(t_elements *)malloc(sizeof(t_elements))))
			ft_exit(l_cmd, errno);
		init_simple_cmd(&parent->s_left, i);
		return (parent);
	}
	tmp = parent->s_left;
	if (!(new = (t_simple_command *)malloc(sizeof(t_simple_command))))
		ft_exit(l_cmd, errno);
	if (!(new->l_element = (t_elements *)malloc(sizeof(t_elements))))
		ft_exit(l_cmd, errno);
	init_simple_cmd(&new, i);
	while (parent->s_left->right != NULL)
		parent->s_left = parent->s_left->right;
	new->parent = parent->s_left;
	parent->s_left->right = new;
	return (parent);
}

t_save		*alloc_store(t_save *save, char *red, int which, int check_io)
{
	t_save	*tmp;
	t_save	*new;

	if (!(new = (t_save *)malloc(sizeof(t_save))))
		return (NULL);
	new->check = which;
	new->cmd_arg = NULL;
	new->file = NULL;
	new->check_io = check_io;
	new->result = 0;
	new->red = red;
	new->next = NULL;
	if (save == NULL)
		return (new);
	tmp = save;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (save);
}
