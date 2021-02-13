/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:51:24 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/12 11:37:00 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_in_str(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			j = 1;
			while (s2[j] && s2[j] == s1[i + j])
				j++;
			if (!s2[j] && !s1[i + j])
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}

int		count_line(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 || !s2))
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int		split_tool_norm(char *str, int i, char c_q)
{
	if (str[i] && (((str[i] == c_q && count_antislach(str, i - 1) == 0)\
			|| str[i] != c_q)))
		return (1);
	return (0);
}

int		split_tool(char *str, int i, char c_q, int index)
{
	if (index == 1)
	{
		if (((str[i] == ' ' || str[i] == '\t') &&\
				count_antislach(str, i - 1)) && str[i])
			return (1);
	}
	else if (index == 2)
	{
		if (str[i] && (((str[i] == ' ' || str[i] == '\t')\
			&& count_antislach(str, i - 1) == 0)\
			|| (str[i] != ' ' && str[i] != '\t')))
			return (1);
	}
	else if (index == 3)
	{
		if (((c_q == 34 && str[i] == c_q && \
			count_antislach(str, i - 1) == 0) || str[i] != c_q) && str[i])
			return (1);
	}
	else if (index == 4)
		return (split_tool_norm(str, i, c_q));
	return (0);
}
