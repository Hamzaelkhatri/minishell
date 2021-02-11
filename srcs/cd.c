/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:29:26 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 18:00:44 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(char *next_path, t_path *path)
{
	char	*tmp;

	path->dollar = 0;
	if (next_path == NULL)
		next_path = search_env(path->env->fullenv, "HOME");
	tmp = getcwd(NULL, 100);
	edit_env(path->env->fullenv, "OLDPWD", tmp);
	frees(&tmp);
	if (strchr(next_path, '\n'))
		next_path = ft_strtrim(next_path, "\n");
	if (chdir(next_path))
	{
		ft_putstr_fd("\e[1;31mbash :", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(next_path, 2);
		path->dollar = 1;
	}
	tmp = getcwd(NULL, 100);
	edit_env(path->env->fullenv, "PWD", tmp);
	frees(&tmp);
}

void	execute_cd(t_command *l_cmd, t_path *path)
{
	if (l_cmd->s_left->right != NULL)
		cd_cmd(l_cmd->s_left->right->l_element->argument, path);
	else
		cd_cmd(NULL, path);
}
