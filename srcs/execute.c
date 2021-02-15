/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:56:51 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/15 15:32:33 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_no(char *cmd)
{
	ft_putstr_fd("bash$ :", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": is a directory", 2);
}

void	errrno_handler(char *cmd)
{
	int		a;
	char	**args;

	args = NULL;
	a = fork();
	if (!a)
	{
		args[0] = ft_strdup("/bin/bash");
		args[1] = ft_strdup("-c");
		args[2] = ft_strdup(cmd);
		if (execve("/bin/bash", args, NULL) == -1)
			err_no(cmd);
		exit(0);
	}
	wait(0);
	free_tab(&args);
}

void	frees_(char **binarypath, char ***tmp)
{
	frees(&*binarypath);
	free_tab(&*tmp);
}

char	**exeuck(char **binarypath, t_path *path, t_command *cmd)
{
	char	*tmp;
	char	*cmds;

	tmp = NULL;
	cmds = NULL;
	if (!ft_strlen(cmd->s_left->l_element->cmd))
		tmp = NULL;
	else
		tmp = ft_strdup(cmd->s_left->l_element->cmd);
	*binarypath = get_directory(path, tmp);
	frees(&tmp);
	if (cmd->s_left->right && cmd->s_left->right->l_element->argument)
		cmds = ft_strjoin_command(cmd->s_left);
	else if (ft_strlen(cmd->s_left->l_element->cmd))
		cmds = ft_strdup(cmd->s_left->l_element->cmd);
	return (args(&cmds));
}

int		execute(t_path *path, t_command *cmd)
{
	char	*binarypath;
	pid_t	a;
	char	**tmp;
	int		status;

	binarypath = NULL;
	status = 0;
	tmp = exeuck(&binarypath, path, cmd);
	if (binarypath)
	{
		a = fork();
		if (a < 0)
			ft_putendl_fd(strerror(errno), 2);
		if (!a)
		{
			if (execve(binarypath, tmp, path->env->fullenv) != 0)
				err_no(binarypath);
			exit(EXIT_SUCCESS);
		}
		wait(&status);
	}
	(status && !path->dollar) ? status_cmd_(status, path) : 0;
	frees_(&binarypath, &tmp);
	return (path->dollar);
}
