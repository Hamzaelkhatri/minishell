/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2020/12/25 15:00:26 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lstsize(t_list_cmd *lst)
{
	t_list_cmd *list1;
	t_pipe *tmp;
	int i;

	list1 = lst;
	i = 0;
	while (lst != NULL)
	{
		tmp = lst->pipe;
		while (lst->pipe)
		{
			lst->pipe = lst->pipe->next;
			i++;
		}
		lst->pipe = tmp;
		lst = lst->next;
	}
	lst = list1;
	return (i);
}

int lstsize_1(t_list_cmd *lst)
{
	t_list_cmd *list1;
	int i;

	i = 0;
	list1 = lst;
	while (lst != NULL)
	{

		i++;
		lst = lst->next;
	}
	lst = list1;
	return (i);
}

void pipes_cmd(char *left, char *right, t_path *path, t_list_cmd *lst)
{
	int fd[2];
	int _fd[2];

	int i;
	// pid_t id1;
	// pid_t id2;
	pid_t pid;
	// char *p;
	// char *tmp;
	// char *read1;
	t_list_cmd *list1;
	t_pipe *tmp1;
	i = 0;

	int s = lstsize(lst);
	list1 = lst;
	while (lst != NULL)
	{
		tmp1 = lst->pipe;
		while (lst->pipe != NULL)
		{
			// printf("hana dkhalte a thaden");
			pipe(fd);

			if ((pid = fork()) == -1)
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0)
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
					close(_fd[1]);
					dup2(fd[1], 1);
					dup2(_fd[0], 0);
				}
				char *binaryPath = "/bin/bash";
				char *const args[] = {binaryPath, "-c", lst->pipe->str_pipe, NULL};
				if (execve(binaryPath, args, path->env->fullenv) < 0)
					exit(1);
			}
			else
			{
				close(fd[1]);
				_fd[0] = fd[0];
				_fd[1] = fd[1];
				lst->pipe = lst->pipe->next;
			}
			i++;
		}
		lst->pipe = tmp1;
		lst = lst->next;
		wait(0);
	}
	lst = list1;
}

void pipes_cmd1(char *left, char *right, t_path *path, t_list_cmd *lst)
{
	int fd[2];
	int _fd[2];

	int i;
	// pid_t id1;
	// pid_t id2;
	pid_t pid;
	// char *p;
	// char *tmp;
	// char *read1;
	t_list_cmd *list1;
	t_pipe *tmp1;
	i = 0;

	list1 = lst;
	int s = lstsize_1(lst);
	// printf("%d\n", s);
	while (lst != NULL)
	{
		// printf("cmd|>%s\n", lst->cmd);
		pipe(fd);

		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
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
				close(_fd[1]);
				dup2(fd[1], 1);
				dup2(_fd[0], 0);
			}
			char *binaryPath = "/bin/bash";
			char *const args[] = {binaryPath, "-c", lst->cmd, NULL};
			if (execve(binaryPath, args, path->env->fullenv) < 0)
				exit(1);
		}
		else
		{
			close(fd[1]);
			_fd[0] = fd[0];
			_fd[1] = fd[1];
			lst = lst->next;
		}
		i++;
	}
	lst = list1;
	wait(0);
}