/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2021/01/05 16:20:56 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int lstsize(t_list_cmd *lst)
{
	t_command *tmp;
	tmp = lst->command;
	int i = 0;
	while(tmp)
	{
		tmp = tmp->right;
		i++;
	}
	return (i);
}

void execute_foreign(t_list_cmd *lst,int piping)
{
	char *cmd;
	char *binaryPath = "/bin/bash";
	int a;
	
	a =0;
	if(!piping)
	{
		a = fork();
	}
	if(!a)
	{
		cmd = ft_strjoin_command(lst->command->s_left);
		char *const args[] = {binaryPath, "-c", cmd,NULL};
		if (execve(binaryPath, args, NULL) < 0)
		perror("bash$ :");
		free(cmd);
	}
}

void    pipes_cmd(t_path * path, t_list_cmd *lst)
{
    int fd[2];
	int _fd[2];
	t_simple_command *s_cmd;


    int i;
    pid_t id1;
    pid_t id2;
    pid_t pid;
    char *p;
    char *tmp;
    char *read1;
	char *cmd;
	// char ss[100];
	i = 0;

	int s = lstsize(lst);
    while (lst->command != NULL)
    {
         pipe(fd);
		if ((pid = fork()) == -1)
        {
			perror("bash $ fork failed");
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
				dup2(fd[1],1);
				dup2(_fd[0], 0);
			}
			if(!cmdcheck(lst->command->s_left->l_element->cmd))
			{
				printf("HELLO");
				execute_foreign(lst,1);
				exit(1);
			}
			else
			{
				// s_cmd = lst->command->s_left;
				// printf("[%s]",lst->command->s_left->l_element->cmd);
				//  puts("Here");
				get_cmd(lst->command->s_left->l_element->cmd,path,lst->command);
				exit(0);
			}
		}
        else 
        {
			close(fd[1]);
			_fd[0] = fd[0];
			_fd[1] = fd[1];
            lst->command = lst->command->right;
        }
		i++;
    }
    wait(0);
}
