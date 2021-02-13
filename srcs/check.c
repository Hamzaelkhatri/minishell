/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:47:07 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/12 11:44:50 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_line_ext2(char *line, int *i)
{
	if (line[*i] == '\\')
	{
		if (count_antislach(line, *i) == 0 && line[*i + 1] == '\0')
			return (0);
	}
	if ((line[*i] == '|' && *i == 0) || (line[*i] == '|' &&\
				check_operation(&line[*i]) == 0))
		return (0);
	else if ((line[*i] == ';' && *i == 0) || (line[*i] == ';'\
				&& check_operation(&line[*i]) == 0))
		return (0);
	else if (line[*i] == '<' && check_operation(&line[*i]) == 0)
		return (0);
	else if (line[*i] == '>' && check_operation(&line[*i]) == 0)
		return (0);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		(*i)++;
	return (1);
}

int			ft_check_line_ext(char *line, int *i)
{
	char	quotes;

	quotes = line[(*i)++];
	while (((quotes == 34 && line[*i] == quotes && count_antislach(line,\
		*i - 1) == 0) || line[*i] != quotes) && line[*i])
		(*i)++;
	if (!(line[*i]))
	{
		ft_putstr_fd("bash : syntax error\n", 2);
		return (258);
	}
	return (1);
}

int			ft_check_line(char *line)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == 39) && count_antislach(line, i - 1))
		{
			if (ft_check_line_ext(line, &i) == 258)
				return (258);
		}
		else
		{
			check = ft_check_line_ext2(line, &i);
			if (check == 0)
			{
				ft_putstr_fd("bash : syntax error\n", 2);
				return (258);
			}
		}
		i++;
	}
	return (0);
}

int			check_type_element(char *line, int count)
{
	int	i;
	int	redirection;
	int	quotes;

	i = 0;
	quotes = 0;
	redirection = -1;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			quotes = (quotes == 0) ? 1 : 0;
		if ((line[i] == '>' || line[i] == '<') &&\
			quotes == 0 && line[i - 1] != '\\')
			return (2);
		i++;
	}
	if (count == 0 && redirection == -1)
		return (1);
	else if (count != 0 && redirection == -1)
		return (3);
	return (0);
}

void		check_element(t_list_cmd *l_cmd)
{
	t_simple_command	*tmp;
	int					i;
	int					result;

	l_cmd->command->tool.i = 0;
	tmp = l_cmd->command->s_left;
	while (l_cmd->command->tool.tab[l_cmd->command->tool.i])
	{
		l_cmd->command->tool.check_io = -1;
		result = check_type_element(l_cmd->command->tool.tab\
			[l_cmd->command->tool.i], l_cmd->command->tool.i);
		l_cmd->command->tool.result = result;
		if (result == 1 || result == 3)
		{
			i = (l_cmd->command->tool.cmd == 0) ? 1 : 2;
			alloc_affect(l_cmd,\
				l_cmd->command->tool.tab[l_cmd->command->tool.i], i, NULL);
		}
		else if (l_cmd->command->tool.result == 2)
			affect_redirection(l_cmd,\
				l_cmd->command->tool.tab[l_cmd->command->tool.i]);
		l_cmd->command->tool.i++;
	}
	l_cmd->command->s_left = tmp;
}
