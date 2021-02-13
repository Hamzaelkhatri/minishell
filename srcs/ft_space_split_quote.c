/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_split_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:48:38 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/12 11:33:56 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	words(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (split_tool(str, i, quote, 1))
			i++;
		if (str[i] && str[i] != ' ' && str[i] != '\t')
			j++;
		while (split_tool(str, i, quote, 2))
		{
			if ((str[i] == 34 || str[i] == 39) && count_antislach(str, i - 1))
			{
				quote = str[i++];
				while (split_tool(str, i, quote, 3))
					i++;
			}
			if (str[i])
				i++;
		}
	}
	return (j);
}

static int	carcts(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] && (((str[i] == ' ' || str[i] == '\t') &&\
			count_antislach(str, i - 1) == 0) ||\
			(str[i] != ' ' && str[i] != '\t')))
	{
		if ((str[i] == 34 || str[i] == 39) && count_antislach(str, i - 1))
		{
			quote = str[i];
			i++;
			while (split_tool(str, i, quote, 3))
				i++;
		}
		i++;
	}
	return (i);
}

static void	check_affec(char ***tab, char *src, int j, int *o)
{
	int		i;
	char	quote;

	i = 0;
	while (src[*o] && (((src[*o] == ' ' || src[*o] == '\t') &&\
			count_antislach(src, *o - 1) == 0) ||\
			(src[*o] != ' ' && src[*o] != '\t')))
	{
		if ((src[*o] == 34 || src[*o] == 39) && count_antislach(src, *o - 1))
		{
			quote = src[*o];
			(*tab)[j][i++] = src[(*o)++];
			while (((quote == 34 && src[*o] == quote && count_antislach(src, \
							*o - 1) == 0) || src[*o] != quote) && src[*o])
			{
				(*tab)[j][i++] = src[(*o)++];
			}
		}
		(*tab)[j][i++] = src[(*o)++];
	}
	(*tab)[j][i] = '\0';
}

static char	*alloc(char **tab, char *src)
{
	int		i;
	int		j;
	int		o;

	j = 0;
	o = 0;
	while (src[o] == ' ' || src[o] == '\t')
		o++;
	while (j < words(src))
	{
		i = 0;
		if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o]) + 1))))
			return (leak(tab, j));
		check_affec(&tab, src, j, &o);
		while ((src[o] == '\t' || src[o] == ' ') && src[o])
			o++;
		j++;
	}
	tab[j] = NULL;
	return (*tab);
}

char		**ft_space_split_quote(char const *s)
{
	int		j;
	char	**tab;
	char	*str;

	j = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	tab = malloc(sizeof(char *) * (words(str) + 1));
	if (!tab)
		return (NULL);
	tab[j] = alloc(tab, str);
	return (tab);
}
