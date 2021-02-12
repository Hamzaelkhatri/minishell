/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:50:05 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:50:11 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			redirection(int check_i_o)
{
	if (check_i_o == 1 || check_i_o == 5 || check_i_o == 9)
		return (2);
	else if (check_i_o == 3 || check_i_o == 7 || check_i_o == 11)
		return (3);
	else if (check_i_o == 2 || check_i_o == 6 || check_i_o == 10)
		return (4);
	else if (check_i_o == 4 || check_i_o == 8 || check_i_o == 12)
		return (5);
	return (0);
}

void		store_ext(t_list_cmd *l_cmd, t_save **save, char **tab_split,\
						int *i)
{
	if ((*save)->result == 4)
	{
		(*save)->cmd_arg = ft_strdup(tab_split[(*i)++]);
		(*save)->file =\
		ft_strdup(l_cmd->command->tool.tab[l_cmd->command->tool.i + 1]);
	}
	else if ((*save)->result == 5)
	{
		(*save)->cmd_arg = ft_strdup(tab_split[(*i)++]);
		(*save)->file = ft_strdup(tab_split[(*i)++]);
	}
}

void		store(t_list_cmd *l_cmd, t_save **save, char **tab_split)
{
	int		i;
	int		result;
	t_save	*tmp;

	tmp = *save;
	i = 0;
	while (*save)
	{
		result = redirection((*save)->check_io);
		(*save)->result = result;
		if (result == 2)
			(*save)->file =\
			ft_strdup(l_cmd->command->tool.tab[l_cmd->command->tool.i + 1]);
		else if (result == 3)
			(*save)->file = ft_strdup(tab_split[i++]);
		else
			store_ext(l_cmd, &(*save), tab_split, &i);
		*save = (*save)->next;
	}
	*save = tmp;
}

void		save_redirection(t_list_cmd *l_cmd, t_save *save)
{
	t_save *tmp;

	tmp = save;
	while (save)
	{
		if (save->result == 3 || save->result == 4 || save->result == 5)
			affect_redirection_ex(l_cmd, save->result, save);
		else if (save->result == 2)
		{
			alloc_affect(l_cmd, save->file, 3, save);
			l_cmd->command->tool.i++;
		}
		save = save->next;
	}
	save = tmp;
}
