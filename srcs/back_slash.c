/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_slash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:58 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:47:00 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		double_quotes(char *line, char **str, int *i, int *index)
{
	(*str)[*index] = line[++(*i)];
	while ((((line[*i] == 34 && count_antislach(line, *i - 1) == 0))\
		|| line[*i] != 34) && line[*i])
	{
		if (line[*i] == '\\' && line[*i + 1] == '\\')
		{
			(*str)[++(*index)] = line[++(*i)];
			(*i)++;
		}
		else if ((line[*i] == '\\' && (line[*i + 1] == 34 ||\
			line[*i + 1] == '$')))
			(*str)[*index] = line[++(*i)];
		else
			(*str)[++(*index)] = line[++(*i)];
	}
	(*str)[*index] = line[++(*i)];
}

void		simple_quotes(char *line, char **str, int *i, int *index)
{
	(*str)[*index] = line[++(*i)];
	while (line[*i] != 39)
		(*str)[++(*index)] = line[++(*i)];
	(*str)[*index] = line[++(*i)];
}

static void	back_slashz(char *line, int i, char **str, int index)
{
	if (!line[i])
		(*str)[index] = '\0';
}

char		*ft_ignoring(char *line)
{
	int		i;
	int		index;
	char	*str;

	i = 0;
	index = 0;
	str = (char *)malloc(ft_strlen(line));
	while (line[i])
	{
		if (line[i] == 34 && count_antislach(line, i - 1))
			double_quotes(line, &str, &i, &index);
		else if (line[i] == 39 && count_antislach(line, i - 1))
			simple_quotes(line, &str, &i, &index);
		else if (line[i] == '\\')
		{
			str[index++] = line[++i];
			i++;
		}
		else
			str[index++] = line[i++];
		if (!line[i])
			str[index] = '\0';
	}
	back_slashz(line, i, &str, index);
	return (str);
}
