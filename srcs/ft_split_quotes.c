/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:02 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/12 11:33:49 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	words(char *str, char c)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		while ((str[i] == c && count_antislach(str, i - 1)) && str[i])
			i++;
		if (str[i] && str[i] != c)
			j++;
		while (split_tool(str, i, c, 4))
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

static int	carcts(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] && (((str[i] == c &&\
		count_antislach(str, i - 1) == 0) || str[i] != c)))
	{
		if ((str[i] == 34 || str[i] == 39) && count_antislach(str, i - 1))
		{
			quote = str[i];
			i++;
			while (split_tool(str, i, quote, 3))
				i++;
		}
		if (str[i])
			i++;
	}
	return (i);
}

static void	check_affec(char ***tab, char *src, int *o, int wich[2])
{
	int		i;
	char	quote;

	i = 0;
	while (src[*o] && ((src[*o] == wich[1] &&\
		count_antislach(src, *o - 1) == 0) ||\
			src[*o] != wich[1]))
	{
		if ((src[*o] == 34 || src[*o] == 39) && count_antislach(src, *o - 1))
		{
			quote = src[*o];
			(*tab)[wich[0]][i++] = src[(*o)++];
			while (((quote == 34 && src[*o] == quote && count_antislach(src, \
				*o - 1) == 0) || src[*o] != quote) && src[*o])
				(*tab)[wich[0]][i++] = src[(*o)++];
		}
		(*tab)[wich[0]][i++] = src[(*o)++];
	}
	(*tab)[wich[0]][i] = '\0';
}

static char	*alloc(char **tab, char *src, char c)
{
	int		j;
	int		o;
	int		wich[2];

	j = 0;
	o = 0;
	while (src[o] == c)
		o++;
	while (j < words(src, c))
	{
		if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o], c) + 1))))
			return (leak(tab, j));
		wich[0] = j;
		wich[1] = c;
		check_affec(&tab, src, &o, wich);
		while (src[o] == c && src[o])
			o++;
		j++;
	}
	tab[j] = NULL;
	return (*tab);
}

char		**ft_split_quotes(char const *s, char c)
{
	int		j;
	char	**tab;
	char	*str;

	j = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	tab = malloc(sizeof(char *) * (words(str, c) + 1));
	if (!tab)
		return (NULL);
	tab[j] = alloc(tab, str, c);
	return (tab);
}
