/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:47:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:52:59 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_correct_r(char operation, char c)
{
	if (operation == '<')
	{
		if ((ft_isalnum(c) == 0) && (c == '\0' || c == '>'\
			|| c == '<' || c == '|' || c == ';'))
			return (0);
	}
	else if (operation == '>')
	{
		if (ft_isalnum(c) == 0 && (c == '\0' || c == '>'\
			|| c == '<' || c == '|' || c == ';'))
			return (0);
	}
	return (1);
}

int	check_is_correct(char operation, char *line)
{
	int		i;
	char	c;

	i = 0;
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	c = line[i];
	if (operation == '|')
	{
		if (ft_isalnum(c) == 0 && (c == '|' || c == ';' || c == '\0'))
			return (0);
	}
	else if (operation == ';')
	{
		if ((ft_isalnum(c) == 0 && c != '\0') && (c == '|' || c == ';'))
			return (0);
	}
	else
		return (check_is_correct_r(operation, c));
	return (1);
}

int	check_operation_r(char *line)
{
	if (line[0] == '>')
	{
		if (line[1] == '>')
		{
			if (check_is_correct(line[0], &line[2]) == 0)
				return (0);
		}
		else if (line[0] == '>')
			if (check_is_correct(line[0], &line[1]) == 0)
				return (0);
	}
	else if (line[0] == '<')
	{
		if (check_is_correct(line[0], &line[1]) == 0)
			return (0);
	}
	return (1);
}

int	check_operation(char *line)
{
	if (line[0] == '|')
	{
		if (check_is_correct(line[0], &line[1]) == 0)
			return (0);
	}
	else if (line[0] == ';')
	{
		if (check_is_correct(line[0], &line[1]) == 0)
			return (0);
	}
	else
		return (check_operation_r(line));
	return (1);
}

int	check_what_after(char c)
{
	if (c != '/' && c != '|' && c != '~' &&\
			c != '\n' && (c == '\'' || c == '"' || ft_isprint(c) == 1))
		return (1);
	return (0);
}
