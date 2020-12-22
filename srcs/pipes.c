/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2020/12/22 17:53:07 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipes_cmd(char *left, char *right, t_path * path, t_list_cmd *lst)
{
    int fd[2];
    int i;
    pid_t id1;
    pid_t id2;
    pid_t pid;
    char *p;
    char *tmp;
    char *read1;
    // if (pipe(fd) == -1)
    // {
    //    puts("An error with open the pipe");
    // }
    // id1 = fork();
    // if (id1 == 0)
    // {
    //     close(fd[1]);
    //     dup2(fd[0],STDIN_FILENO);
    //     close(fd[0]);
    //     getprogramme(path, right);
    //     exit(0);
    // }
    // else if (id1 < 0)
    // {
    //     puts("fork error");
    // }
    // else
    // {
    //     id2 = fork();
    //     if (id2 == 0)
    //     {
    //         close(fd[0]);
    //         dup2(fd[1], STDOUT_FILENO);
    //         close(fd[1]);
    //         getprogramme(path, left);
    //         exit(0);
    //     }
    //     close(fd[0]);
    //     close(fd[1]);
    //     waitpid(-1, NULL, 0);
    //     waitpid(-1, NULL, 0);
    // }
    // if (lst->pipe == NULL)
    //     puts("ha li glna asahbi");
    while (lst->pipe != NULL)
    {
        pipe(fd);
		if ((pid = fork()) == -1)
        {
			perror("fork");
			exit(1);
		}
        if (pid == 0) 
        {
			dup2(fd[0], 0);
			if (lst->pipe->str_pipe != NULL)
            {
    			close(fd[1]);
				dup2(fd[1], 1);
			}
			close(fd[0]);
            getprogramme(path, lst->pipe->str_pipe);

            exit(0);
		}
        else 
        {
        puts(lst->pipe->str_pipe);
			// wait(0);
			close(fd[1]);
            waitpid(-1, NULL, 0);
            lst->pipe = lst->pipe->next;
        }
    }
}
