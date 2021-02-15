/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:51:44 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/15 12:35:49 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extraire_variable(char *line, int i, int *index)
{
	int		result;
	char	*str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	result = *index + 2;
	str = (char *)malloc(result);
	if (*index == -1)
		str[j++] = '$';
	else
	{
		while (j < *index + 1)
			str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}

char	*ft_variables(char *line, int i, int *index)
{
	char	*str;

	str = NULL;
	*index = ft_check_variable(line, i);
	if (*index == 0)
		return (NULL);
	else
		str = ft_extraire_variable(line, i, index);
	return (str);
}

void	concat_ext(char **str1, char **dupstr, char **tmp, int index)
{
	char	*tmp1;

	tmp1 = *dupstr;
	if (index == 1)
		*str1 = ft_strjoin(*dupstr, *str1);
	else
		*str1 = ft_strjoin(*str1, *dupstr);
	frees(&tmp1);
	frees(&(*tmp));
}

void	affectation_dollar(char **str, char **ptr, int *i, int index)
{
	char	*ptr_s;

	ptr_s = *str;
	*str = ft_concatenation(*str, i, index, *ptr);
	frees(&ptr_s);
	frees(ptr);
}

void	check_variable(char **str, int *i, int index, t_path *path)
{
	char	*var;
	char	*ptr;

	if ((var = ft_variables(*str, *i, &index)))
	{
		if (var[0] == '$' && var[1] == '?' && var[2] == '\0')
			ptr = ft_itoa(path->dollar);
		else
		{
			ptr = (get_var_env1(path, var)) ?\
				ft_strdup(get_var_env1(path, var)) : NULL;
		}
		affectation_dollar(&(*str), &ptr, i, index);
	}
	if (var)
		frees(&var);
}
