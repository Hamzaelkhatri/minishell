/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:30 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:49:31 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parcs_simple_command(char *s_command, t_list_cmd *l_cmd)
{
	t_command	*tmp_command;

	tmp_command = l_cmd->command;
	if (l_cmd->command->s_left->l_element != NULL)
		l_cmd->command = add_command(l_cmd->command, l_cmd);
	while (l_cmd->command->right != NULL)
		l_cmd->command = l_cmd->command->right;
	ft_bzero(&l_cmd->command->tool, sizeof(t_tool));
	l_cmd->command->tool.tab = ft_space_split_quote(s_command);
	check_element(l_cmd);
	free_tab(&l_cmd->command->tool.tab);
	l_cmd->command = tmp_command;
}

void	parse_command(t_list_cmd *l_cmd, char *line)
{
	int			index;
	char		**tab;
	t_list_cmd	*tmp;

	index = 0;
	tmp = l_cmd;
	if (l_cmd->command->s_left->l_element != NULL)
		l_cmd = add_list_cmd(l_cmd);
	while (l_cmd->next != NULL)
		l_cmd = l_cmd->next;
	tab = ft_split_quotes(line, '|');
	while (tab[index])
		parcs_simple_command(tab[index++], l_cmd);
	l_cmd = tmp;
	free_tab(&tab);
}

void	parse_list_command(t_list_cmd *l_cmd, char *line)
{
	char	**tab;
	int		index;

	index = 0;
	tab = ft_split_quotes(line, ';');
	while (tab[index])
		parse_command(l_cmd, tab[index++]);
	free_tab(&tab);
}
