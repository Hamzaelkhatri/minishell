/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:56:51 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/10 19:28:51 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_paths(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
		return (127);
	return (0);
}

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

	args[0] = ft_strdup("/bin/bash");
	args[1] = ft_strdup("-c");
	args[2] = ft_strdup(cmd);
	args[3] = ft_strdup(NULL);
	a = fork();
	if (!a)
	{
		if (execve("/bin/bash", args, path->env->fullenv) == -1)
			perror("bash$ ");
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
	if (status && !path->dollar)
		status_cmd_(status, path);
	frees_(&binarypath, &tmp, &cmds);
	return (path->dollar);
}
