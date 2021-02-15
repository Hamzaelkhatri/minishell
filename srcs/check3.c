/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:47:27 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/15 15:31:34 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_variable(char *line, int i)
{
	int	j;

	j = 0;
	i++;
	if (line[i] == '"' || line[i] == '\'')
		return (-1);
	if (line[i] == '$')
		return (0);
	else if (line[i] == '?')
		return (1);
	while (ft_isalnum(line[i]) || line[i] == '_')
	{
		i++;
		j++;
	}
	return (j);
}

int		check_end(char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	if ((line[i - 1] == '>' || line[i - 1] == '<') &&\
		(count_antislach(line, i - 2)))
		return (1);
	else
		return (0);
}

void	check_join_r(t_list_cmd *l_cmd, char **str, char *line)
{
	char	*tmp_f;

	*str = ft_strdup(line);
	if (check_end(*str))
	{
		tmp_f = *str;
		*str = ft_strjoin(*str,\
			l_cmd->command->tool.tab[++l_cmd->command->tool.i]);
		frees(&tmp_f);
		while (l_cmd->command->tool.tab[l_cmd->command->tool.i + 1] &&\
			check_end(l_cmd->command->tool.tab[l_cmd->command->tool.i + 1]))
		{
			tmp_f = *str;
			*str = ft_strjoin(*str,\
				l_cmd->command->tool.tab[++l_cmd->command->tool.i]);
			frees(&tmp_f);
		}
	}
}

int		check_redirection(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		if (line[*i + 2] == '\0')
			return (*i == 0) ? (5) : (6);
		else if (check_what_after(line[*i + 2]) == 1)
			return (*i == 0) ? (7) : (8);
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '\0')
			return (*i == 0) ? (1) : (2);
		else if (check_what_after(line[*i + 1]) == 1)
			return (*i == 0) ? (3) : (4);
	}
	else if (line[*i] == '<' && line[*i + 1] != '<')
	{
		if (line[*i + 1] == '\0')
			return (*i == 0) ? (9) : (10);
		else if (check_what_after(line[*i + 1]) == 1)
			return (*i == 0) ? (11) : (12);
	}
	return (0);
}
