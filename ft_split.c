/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 23:27:26 by zjamali           #+#    #+#             */
/*   Updated: 2019/11/13 17:35:25 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		words(char *str, char c)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] && str[i] != c)
		{
			i++;
			j++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	return (j);
}

static void		*leak(char **spl, int j)
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

static int		carcts(char *str, char c)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

static char		*allocandfill(char **tab, char *src, char c)
{
	int			i;
	int			j;
	int			k;

	j = 0;
	k = 0;
	while (src[k] == c)
		k++;
	while (j < words(src, c))
	{
		i = 0;
		if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[k], c) + 1))))
			return (leak(tab, j));
		while (src[k] != c && src[k])
			tab[j][i++] = src[k++];
		tab[j][i] = '\0';
		while (src[k] == c && src[k])
			k++;
		j++;
	}
	tab[j] = NULL;
	return (*tab);
}

char			**ft_split(char const *s, char c)
{
	int			i;
	int			j;
	int			k;
	char		**tab;
	char		*str;

	k = 0;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	tab = malloc(sizeof(char *) * (words(str, c) + 1));
	if (!tab)
		return (NULL);
	tab[j] = allocandfill(tab, str, c);
	return (tab);
}
