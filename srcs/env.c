/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:34:06 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 18:00:32 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_env(char **env, char *var, char *res)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!res)
		res = "";
	if (search_env(env, var))
		while (env[i])
		{
			if (!ft_strncmp(env[i], var, ft_strlen(var)))
			{
				k = 0;
				j = cout_to_char(env[i], '=') + 1;
				res = ft_strjoin("=", res);
				env[i] = ft_strjoin(var, res);
				frees(&res);
			}
			i++;
		}
}

void	show_env(char **env)
{
	int		i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (check_equal(env[i]))
			ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	execute_env(t_path *path)
{
	show_env(path->env->fullenv);
	path->dollar = 0;
}
