/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:10:30 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/15 15:46:59 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_working_directory(t_path *path)
{
	char	*pwd;

	pwd = search_env(path->env->fullenv, "PWD");
	if (pwd)
		ft_putendl_fd(pwd, 1);
	else
		ft_putendl_fd(getcwd(pwd, 100), 1);
}

void		execute_pwd(t_path *path)
{
	print_working_directory(path);
	path->dollar = 0;
}

int			size_args(t_command *l_cmd)
{
	int					i;
	t_simple_command	*tmp;

	tmp = l_cmd->s_left->right;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->right;
	}
	return (i);
}

int			check_paths(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
		return (127);
	return (0);
}

char		**args(char **cmd)
{
	char	**tmp;

	tmp = ft_split(*cmd, ' ');
	frees(&*cmd);
	return (tmp);
}
