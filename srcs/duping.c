/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:09:50 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/12 09:26:40 by helkhatr         ###   ########.fr       */
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

void	close_dup(int fd1, int fd2, int fd3)
{
	close(fd1);
	dup2(fd2, fd3);
}

void	close_fd(int i, int fd1, int fd2)
{
	if (i > 0)
		close(fd1);
	close(fd2);
}

void	backup_fd(int fd1[2], int fd2[2])
{
	fd1[0] = fd2[0];
	fd1[1] = fd2[1];
}

void	exec_fd(int i, t_list_cmd *lst, int fd[2], int fd_[2])
{
	if (i == 0)
		close_dup(fd[0], fd[1], 1);
	else if (i == lstsize(lst) - 1)
		close_dup(fd_[1], fd_[0], 0);
	else
	{
		close_dup(fd[0], fd[1], 1);
		close_dup(fd_[1], fd_[0], 0);
	}
}
