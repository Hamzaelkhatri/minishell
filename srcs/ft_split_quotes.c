/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:58:00 by sqatim            #+#    #+#             */
/*   Updated: 2019/11/08 22:40:49 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int words(char *str, char c)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] && str[i] != c)
			j++;
		while (str[i] && str[i] != c)
		{
			if ((str[i] == 34 || str[i] == 39) && str[i - 1] != '\\')
			{
				quote = str[i++];
				while ((str[i] == quote && str[i - 1] == '\\') || str[i] != quote)
					i++;
			}
			i++;
		}
	}
	return (j);
}

static void *leak(char **spl, int j)
{
	j = j - 1;
	while (spl[j])
	{
		free(spl[j]);
		j--;
	}
	free(spl);
	return (NULL);
}

static int carcts(char *str, char c)
{
	int i;
	char quote;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if ((str[i] == 34 || str[i] == 39) && str[i - 1] != '\\')
		{
			quote = str[i];
			i++;
			while ((str[i] == quote && str[i - 1] == '\\') || str[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

static char *alloc(char **tab, char *src, char c)
{
	int i;
	int j;
	int o;
	char quote;

	j = 0;
	o = 0;
	while (src[o] == c)
		o++;
	while (j < words(src, c))
	{
		i = 0;
		if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o], c) + 1))))
			return (leak(tab, j));
		while (src[o] != c && src[o])
		{
			if ((src[o] == 34 || src[o] == 39) && src[o - 1] != '\\')
			{
				quote = src[o];
				tab[j][i++] = src[o++];
				while ((src[o] == quote && src[o - 1] == '\\') || src[o] != quote)
					tab[j][i++] = src[o++];
			}
			tab[j][i++] = src[o++];
		}
		tab[j][i] = '\0';
		while (src[o] == c && src[o])
			o++;
		j++;
	}
	tab[j] = NULL;
	return (*tab);
}

char **ft_split_quotes(char const *s, char c)
{
	int j;
	char **tab;
	char *str;

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
