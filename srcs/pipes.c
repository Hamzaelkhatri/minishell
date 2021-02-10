/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/10 18:59:12 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lstsize(t_list_cmd *lst)
{
	t_command *tmp;
	tmp = lst->command;
	int i = 0;
	while (tmp)
	{
		tmp = tmp->right;
		i++;
	}
	return (i);
}

void pipes_cmd(t_path *path, t_list_cmd *lst)
{
	int fd[2];
	int _fd[2];
	int i;
	pid_t pid[4000];
	int status;

	i = 0;
	int s = lstsize(lst);
	t_command *tmp = lst->command;
	while (tmp != NULL)
	{
		pipe(fd);
		if ((pid[i] = fork()) == -1)
		{
			ft_putendl_fd(strerror(errno), 1);
			exit(0);
		}
		else if (pid[i] == 0)
		{
			if (i == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
			}
			else if (i == s - 1)
			{
				close(_fd[1]);
				dup2(_fd[0], 0);
			}
			else
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(_fd[1]);
				dup2(_fd[0], 0);
			}
			get_cmd_(tmp->s_left->l_element->cmd, path, tmp);
			exit(pid[i]);
		}
		else
		{
			status_cmd_(pid[i], path);
			if (i > 0)
				close(_fd[0]);
			close(fd[1]);
			_fd[0] = fd[0];
			_fd[1] = fd[1];
			tmp = tmp->right;
			i++;
		}
	}
	
	while (0 < i)
	{
		wait(&status);
		i--;
		if (status && !path->dollar)
			path->dollar= status_cmd_(status,path);
	}
}
