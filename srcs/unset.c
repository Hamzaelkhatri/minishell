/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:23:11 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/13 17:06:01 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		frees_unset(char **tmp1, char **tmp2)
{
	frees(&*tmp1);
	frees(&*tmp2);
}

int			check_unset(char *name, t_path *path, int i)
{
	char	*tmp1;
	char	*tmp2;
	int		ret;

	ret = 0;
	tmp2 = get_befor_equal(path->env->fullenv[i]);
	tmp1 = get_befor_equal(name);
	if (!ft_strcmp(tmp1, tmp2))
		ret = 0;
	else
		ret = 1;
	frees_unset(&tmp1, &tmp2);
	return (ret);
}

void		unset_cmd(char *name, t_path *path)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	j = 0;
	check = 0;
	name = ft_strtrim(name, "\n");
	while (path->env->fullenv[i])
	{
		if (!check_unset(name, path, i))
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
	frees(&name);
	path->env->fullenv[j] = (j) ? NULL : path->env->fullenv[j];
}

void		execute_unset(t_path *path, t_command *l_cmd)
{
	unset_cmd(l_cmd->s_left->right->l_element->argument, path);
	path->dollar = 0;
}
