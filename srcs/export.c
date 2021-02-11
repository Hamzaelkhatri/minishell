/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:21:39 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 18:39:38 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_befor_equal(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!(ptr = malloc(sizeof(char) * (cout_to_char(str, '=') + 1))))
		return (NULL);
	while (str[i] != '=' && str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_after_equal(char *str)
{
	int		i;
	char	*tmp;

	tmp = get_befor_equal(str);
	if (!check_equal(str))
	{
		frees(&tmp);
		return (NULL);
	}
	i = ft_strlen(tmp);
	frees(&tmp);
	return (&str[i + 1]);
}

void	show_export(char **env)
{
	int		i;
	char	*tmp;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		tmp = get_befor_equal(env[i]);
		if (ft_strncmp("_", tmp, ft_strlen(env[i])))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp, 1);
			if (get_after_equal(env[i]))
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(get_after_equal(env[i]), 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		frees(&tmp);
		i++;
	}
}

int		check_space(char *str)
{
	int i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	i = 0;
	while (str[++i] != '=')
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

char	*get_to_space(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!(ptr = malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	ft_bzero(ptr, ft_strlen(str));
	while (str[i])
	{
		ptr[i] = str[i];
		if (str[i] == ' ')
			break ;
		i++;
	}
	return (ptr);
}
