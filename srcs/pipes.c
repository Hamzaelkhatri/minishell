/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:09:50 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/12 09:22:41 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting_childs(t_path *path, int i)
{
	int		status;

	status = 0;
	while (0 < i)
	{
		wait(&status);
		i--;
		if (!path->dollar)
			path->dollar = status_cmd_(status, path);
	}
}

void	exit_err(void)
{
	ft_putendl_fd(strerror(errno), 1);
	exit(0);
}

void	cmd_exec(t_path *path, t_command *tmp)
{
	get_cmd_(tmp->s_left->l_element->cmd, path, tmp);
	exit(0);
}

void	pipes_cmd(t_path *path, t_list_cmd *lst)
{
	int			fd[2];
	int			fd_[2];
	int			i;
	pid_t		pid[4000];
	t_command	*tmp;

	i = 0;
	tmp = lst->command;
	while (tmp != NULL)
	{
		((!pipe(fd) && (pid[i] = fork()) == -1)) ? exit_err() : 0;
		if (pid[i] == 0)
		{
			exec_fd(i, lst, fd, fd_);
			cmd_exec(path, tmp);
		}
		else
		{
			close_fd(i, fd_[0], fd[1]);
			backup_fd(fd_, fd);
			tmp = tmp->right;
			i++;
		}
	}
	waiting_childs(path, i);
}
