/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:57:15 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/12 10:17:12 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*beginchar(char const *s, const char *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] && set[j])
	{
		if (s[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	return ((char *)&s[i]);
}

static int	endofchar(const char *s, const char *set)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(s);
	if (!s || !set)
		return (0);
	j--;
	while (j > 0 && set[i])
	{
		if (set[i] == s[j])
		{
			j--;
			i = 0;
		}
		else
		{
			i++;
		}
	}
	return (j);
}

char		*ft_strtrim(char const *s, const char *set)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s || !set)
		return (NULL);
	s = beginchar(s, set);
	tmp = (char *)malloc(sizeof(char) * endofchar(s, set) + 2);
	if (tmp == NULL)
		return (NULL);
	while (i < endofchar(s, set) + 1)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
