/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:51:34 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/15 15:48:36 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	after_dollar(char *str, int *i)
{
	if (str[*i] && ((str[*i] == '$' && (str[*i + 1] == '$' || !str[*i + 1]\
		|| str[*i + 1] == '\\' || !ft_isalnum(str[*i + 1]))) ||\
			(str[*i] == '$' && count_antislach(str, *i - 1) == 0) ||\
				str[*i] != '$'))
		(*i)++;
}

char	*dollars(char *line, t_path *path)
{
	int		i;
	int		index;
	int		save;
	char	*str;

	i = 0;
	save = 0;
	index = 0;
	str = ft_strdup(line);
	while (str[i])
	{
		if (str[i] == 34 && count_antislach(str, i - 1))
			save = (save == 0) ? 1 : 0;
		if (str[i] == 39 && count_antislach(str, i - 1) && save == 0)
		{
			i++;
			while (str[i] != 39 && str[i])
				i++;
		}
		else if (check_if_in(str, i, save))
			check_variable(&str, &i, index, path);
		else
			after_dollar(str, &i);
	}
	return (str);
}

void	variables_affect(char **cmd, t_path *path)
{
	char *tmp;
	char *str;

	tmp = ft_strdup(*cmd);
	str = tmp;
	tmp = dollars(tmp, path);
	frees(&str);
	frees(cmd);
	*cmd = ft_ignoring(tmp);
	free(tmp);
}

void	variables_extended(t_list_cmd *l_cmd,
						t_simple_command *tmp_s, t_path *path)
{
	while (l_cmd->command != NULL)
	{
		tmp_s = l_cmd->command->s_left;
		while (l_cmd->command->s_left != NULL)
		{
			if (l_cmd->command->s_left->l_element->indice == 1)
				variables_affect(&l_cmd->command->s_left->l_element->cmd,
								path);
			else if (l_cmd->command->s_left->l_element->indice == 2)
				variables_affect(&l_cmd->command->s_left->l_element->argument,
								path);
			else if (l_cmd->command->s_left->l_element->indice == 3)
				variables_affect(&l_cmd->command->s_left->l_element\
					->redirection.file, path);
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		}
		l_cmd->command->s_left = tmp_s;
		l_cmd->command = l_cmd->command->right;
	}
}

void	variables(t_list_cmd *l_cmd, t_path *path)
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
		variables_extended(l_cmd, tmp_s, path);
		l_cmd->command = tmp_command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp_l_command;
}
