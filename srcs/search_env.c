/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:34:19 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/13 11:55:54 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_to_equal(const char *s1, const char *s2, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			j = 1;
			while (s2[j] && s2[j] == s1[i + j] && (i + j) < len)
				j++;
			if (!s2[j] && s1[i + j] == '=')
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}

int		cout_to_char(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char	*search_env(char **env, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*eq;

	eq = NULL;
	j = ft_strlen(str) + 1;
	i = 0;
	while (env[i])
	{
		eq = get_befor_equal(env[i]);
		if (!ft_strcmp(eq, str))
		{
			frees(&eq);
			tmp = ft_str_to_equal(env[i], str, ft_strlen(str));
			return (&tmp[j]);
		}
		frees(&eq);
		i++;
	}
	return (NULL);
}
