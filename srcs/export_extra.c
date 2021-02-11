/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:39:09 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 18:42:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_extern_value(char *str)
{
	int i;

	i = 0;
	if (str[0] == '=' || !str[0] || ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ret_err(char *tmp, t_path *path)
{
	ft_putstr_fd("\e[1;31mexport :\e[1;31m", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(" bad assignment\n", 2);
	path->dollar = 127;
}

void	export_extra(t_path *path, char *name, char *tmp)
{
	char	*tmp1;
	int		line;

	line = 0;
	if (!check_equal(name))
	{
		tmp1 = name;
		name = ft_strjoin(name, "");
		frees(&tmp1);
	}
	if (!search_env(path->env->fullenv, tmp))
	{
		line = count_line(path->env->fullenv);
		path->env->fullenv[line] = name;
		path->env->fullenv[line + 1] = NULL;
	}
	else if (check_equal(name))
		edit_env(path->env->fullenv, tmp, get_after_equal(name));
	path->dollar = 0;
}

int		export_cmd(char *name, t_path *path)
{
	char	*tmp;

	name = ft_strtrim(name, "\n");
	tmp = get_befor_equal(name);
	if (!get_extern_value(tmp))
		ret_err(tmp, path);
	else
		export_extra(path, name, tmp);
	frees(&tmp);
	return (1);
}

int		check_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
