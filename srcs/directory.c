/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:34:58 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/15 14:27:40 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_link(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (127);
		i++;
	}
	return (0);
}

int		bash_err(char *cmd)
{
	ft_putstr_fd("\e[1;31mbash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

char	*directory_(t_path *path, char *cmd)
{
	char	*tmps;
	char	*link;

	tmps = NULL;
	if (check_link((cmd)))
	{
		if (!(path->dollar = check_paths((cmd))))
			return (ft_strdup(cmd));
		path->dollar = bash_err(cmd);
	}
	else
	{
		link = ft_strjoin(getcwd(NULL, 100), "/");
		link = ft_strjoin(link, (cmd));
		if (!(path->dollar = check_paths(link)))
			return (link);
		else
			path->dollar = bash_err(cmd);
		frees(&link);
	}
	return (NULL);
}

char	*get_directory_two(t_path *path, char *cmd, char *tmp)
{
	char	**paths;
	int		i;
	char	*link;
	char	*tmps;

	i = 0;
	paths = ft_split(tmp, ':');
	while (paths[i])
	{
		link = ft_strjoin(paths[i], "/");
		tmps = link;
		link = ft_strjoin(link, cmd);
		frees(&tmps);
		tmps = link;
		if (!(path->dollar = check_paths(link)))
		{
			free_tab(&paths);
			return (link);
		}
		frees(&link);
		i++;
	}
	free_tab(&paths);
	path->dollar = bash_err(cmd);
	return (NULL);
}

char	*get_directory(t_path *path, char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	if (cmd)
	{
		tmp = search_env(path->env->fullenv, "PATH");
		if (tmp && !check_link((cmd)))
			return (get_directory_two(path, cmd, tmp));
		else
			return (directory_(path, cmd));
	}
	return (NULL);
}
