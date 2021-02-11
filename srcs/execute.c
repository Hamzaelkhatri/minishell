/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:56:51 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/11 12:22:10 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**args(char *cmd, t_path *path)
{
	return (ft_split(cmd, ' '));
}

int		status_cmd_(int status, t_path *path)
{
	if (WIFEXITED(status))
		path->dollar = WEXITSTATUS(status);
	else
		path->dollar = 0;
	return (path->dollar);
}

void	errrno_handler(t_path *path, char *cmd)
{
	int		a;
	char	**args;

	a = fork();
	if (!a)
	{
		args[0] = ft_strdup("/bin/bash");
		args[1] = ft_strdup("-c");
		args[2] = ft_strdup(cmd);
		if (execve("/bin/bash", args, NULL) == -1)
		{
			ft_putstr_fd("bash$ :", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": is a directory", 2);
		}
		exit(0);
	}
	wait(0);
	free_tab(&args);
}

void	frees_(char **binarypath, char ***tmp, char **cmds)
{
	frees(&*binarypath);
	free_tab(&*tmp);
	frees(&*cmds);
}

int		execute(t_path *path, t_command *cmd)
{
	char	*binarypath;
	pid_t	a;
	char	**tmp;
	char	*cmds;
	int		status;

	binarypath = get_directory(path, cmd->s_left->l_element->cmd);
	cmds = ft_strjoin_command(cmd->s_left);
	tmp = args(cmds, path);
	if (binarypath)
	{
		a = fork();
		if (a < 0)
			ft_putendl_fd(strerror(errno), 1);
		if (!a)
		{
			if (execve(binarypath, tmp, path->env->fullenv) != 0)
				errrno_handler(path, cmds);
			exit(EXIT_SUCCESS);
		}
		wait(&status);
	}
	(status && !path->dollar) ? status_cmd_(status, path) : 0;
	frees_(&binarypath, &tmp, &cmds);
	return (path->dollar);
}
