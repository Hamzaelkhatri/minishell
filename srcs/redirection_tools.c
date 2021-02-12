/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:50 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:49:58 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		affect_redirection_ex(t_list_cmd *l_cmd, int result, t_save *save)
{
	if (result == 3)
		alloc_affect(l_cmd, save->file, 3, save);
	else if (result == 4 || result == 5)
	{
		if (l_cmd->command->tool.cmd == 0)
			alloc_affect(l_cmd, save->cmd_arg, 1, NULL);
		else
			alloc_affect(l_cmd, save->cmd_arg, 2, NULL);
		if (result == 4)
		{
			alloc_affect(l_cmd, save->file, 3, save);
			l_cmd->command->tool.i++;
		}
		else if (result == 5)
			alloc_affect(l_cmd, save->file, 3, save);
	}
}

void		in_boucle_r_ext(t_save **save, int check_i_o, int wich, int *index)
{
	if (wich == 1)
	{
		if ((check_i_o == 2 || check_i_o == 4) && *index == 1)
			check_i_o = (check_i_o == 2) ? 1 : 3;
		if ((check_i_o == 2 || check_i_o == 4) && *index == 0)
			*save = alloc_store(*save, ">", 1, check_i_o);
		else
			*save = alloc_store(*save, ">", 2, check_i_o);
		*index = 1;
	}
	else if (wich == 2)
	{
		if ((check_i_o == 10 || check_i_o == 12) && *index == 1)
			check_i_o = (check_i_o == 10) ? 9 : 11;
		if ((check_i_o == 10 || check_i_o == 12) && *index == 0)
			*save = alloc_store(*save, "<", 1, check_i_o);
		else
			*save = alloc_store(*save, "<", 2, check_i_o);
		*index = 1;
	}
}

void		in_boucle_r(char *str, int *i, t_save **save, int *index)
{
	int	check_i_o;

	check_i_o = check_redirection(str, i);
	if (check_i_o == 1 || check_i_o == 2 || check_i_o == 3 || check_i_o == 4)
		in_boucle_r_ext(&(*save), check_i_o, 1, index);
	else if (check_i_o == 5 || check_i_o == 6 || check_i_o == 7\
		|| check_i_o == 8)
	{
		str[(*i)++] = ' ';
		if ((check_i_o == 6 || check_i_o == 8) && *index == 1)
			check_i_o = (check_i_o == 6) ? 5 : 7;
		if ((check_i_o == 6 || check_i_o == 8) && *index == 0)
			*save = alloc_store(*save, ">>", 1, check_i_o);
		else
			*save = alloc_store(*save, ">>", 2, check_i_o);
		*index = 1;
	}
	else
		in_boucle_r_ext(&(*save), check_i_o, 2, index);
}

void		affect_redirection_ext(t_list_cmd *l_cmd, t_save **save, char **str)
{
	char **tab_split;

	tab_split = ft_space_split_quote(*str);
	store(l_cmd, &(*save), tab_split);
	free_tab(&tab_split);
	frees(&(*str));
	save_redirection(l_cmd, *save);
	free_redirection(&(*save));
}

void		affect_redirection(t_list_cmd *l_cmd, char *line)
{
	int		i;
	int		index;
	char	quotes;
	char	*str;
	t_save	*save;

	i = 0;
	quotes = 0;
	save = NULL;
	index = 0;
	check_join_r(l_cmd, &str, line);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quotes = (quotes == 0) ? 1 : 0;
		if ((str[i] == '>' || str[i] == '<') &&\
			quotes == 0 && str[i - 1] != '\\')
		{
			in_boucle_r(str, &i, &save, &index);
			str[i] = ' ';
		}
		i++;
	}
	affect_redirection_ext(l_cmd, &save, &str);
}
