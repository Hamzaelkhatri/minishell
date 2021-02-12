/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:23:11 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/12 10:40:43 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset_cmd(char *name, t_path *path)
{
	int		i;
	int		j;
	char	**spl;
	int		check;

	i = 0;
	j = 0;
	check = 0;
	ft_strchr(name, '\n') ? name = ft_strtrim(name, "\n") : 0;
	while (path->env->fullenv[i])
	{
		if (!ft_strcmp(get_befor_equal(path->env->fullenv[i]),
					get_befor_equal(name)))
		{
			j = i;
			while (path->env->fullenv[j])
			{
				path->env->fullenv[j] = path->env->fullenv[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
	path->env->fullenv[j] = (j) ? NULL : path->env->fullenv[j];
}

void		execute_unset(t_path *path, t_command *l_cmd)
{
	unset_cmd(l_cmd->s_left->right->l_element->argument, path);
	path->dollar = 0;
}
