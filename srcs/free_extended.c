/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:48:19 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/15 14:49:24 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_scommand(t_simple_command **scommand)
{
	if (*scommand != NULL)
		free_scommand(&(*scommand)->right);
	if (*scommand != NULL)
		free_s_command(&(*scommand));
}

void	free_command(t_command **command)
{
	if (*command != NULL)
		free_command(&(*command)->right);
	if (*command != NULL)
	{
		free_scommand(&(*command)->s_left);
		if ((*command)->tool.tab != NULL)
			free_tab(&(*command)->tool.tab);
		free(*command);
		*command = NULL;
	}
}

void	free_lcommand(t_list_cmd **l_command)
{
	if (*l_command != NULL)
		free_lcommand(&(*l_command)->next);
	if (*l_command != NULL)
	{
		free_command(&(*l_command)->command);
		if ((*l_command)->line != NULL)
			ft_strdel(&(*l_command)->line);
		free(*l_command);
		*l_command = NULL;
	}
}

void	frees(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
