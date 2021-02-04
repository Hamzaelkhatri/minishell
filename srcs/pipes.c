/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/04 15:47:03 by helkhatr         ###   ########.fr       */
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
	while (lst->command != NULL)
	{
		// if(f != 1)
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
			lst->command->s_left->l_element->cmd = ft_strtrim(lst->command->s_left->l_element->cmd, "\n");
			get_cmd_(lst->command->s_left->l_element->cmd, path, lst->command);
			exit(path->dollar);//
		}
		else
		{
			_status_cmd(pid[i], path);
			if (i > 0)
				close(_fd[0]);
			close(fd[1]);
			_fd[0] = fd[0];
			_fd[1] = fd[1];
			lst->command = lst->command->right;
			i++;
		}
	}
	while (0 < i)
	{
		wait(&status);
		i--;
		if (status && !path->dollar)
			path->dollar= _status_cmd(status,path);
	}
}
