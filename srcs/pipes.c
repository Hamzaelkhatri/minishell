/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:10:18 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 19:30:13 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lstsize(t_list_cmd *lst)
{
	t_command	*tmp;
	int			i;

	tmp = lst->command;
	i = 0;
	while (tmp)
	{
		tmp = tmp->right;
		i++;
	}
	return (i);
}

void	pipe_cmd_(int i, int fd[2], int fd_[2], t_list_cmd *lst)
{
	int	s;

	s = lstsize(lst);
	if (i == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	}
	else if (i == s - 1)
	{
		close(fd_[1]);
		dup2(fd_[0], 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd_[1]);
		dup2(fd_[0], 0);
	}
}

void	pipe_extra(int pid, t_path *path, int fd_[2], int fd[2])
{
	status_cmd_(pid, path);
	close(fd_[0]);
	close(fd[1]);
	fd_[0] = fd[0];
	fd_[1] = fd[1];
}

void	waiting_childs(t_path *path, int i)
{
	int		status;

	while (0 < i)
	{
		wait(&status);
		i--;
		if (status && !path->dollar)
			path->dollar = status_cmd_(status, path);
	}
}

void	err_affec()
{
	ft_putendl_fd(strerror(errno), 1);
	exit(0);
}

void	pipes_cmd(t_path *path, t_list_cmd *lst)
{
	int			fd[2];
	int			fd_[2];
	int			i;
	pid_t		pid;
	t_command	*tmp;

	i = 0;
	tmp = lst->command;
	while (tmp != NULL)
	{
		pipe(fd);
		if ((pid = fork()) == -1)
			err_affec();
		else if (pid == 0)
		{
			pipe_cmd_(i, fd, fd_, lst);
			get_cmd_(tmp->s_left->l_element->cmd, path, tmp);
			exit(0);
		}
		else
		{
			pipe_extra(pid, path, fd_, fd);
			tmp = tmp->right;
			i++;
		}
	}
	waiting_childs(path, i);
}
