/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2020/12/21 14:44:58 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipes_cmd(char *left, char *right, t_path * path)
{
    int fd[2];
    int i = 0;
    pid_t id1;
    pid_t id2;
    char *p;
    char *tmp;
    char *read1;
    if (pipe(fd) == -1)
    {
       puts("An error with open the pipe");
    }
    id1 = fork();
	if (!id1)
    {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        getprogramme(path, right);
		exit(0);
    }
    else
    {
        id2 = fork();
        if (!id2)
        {
            close(fd[0]);               
            dup2(fd[1], STDOUT_FILENO);  
            close(fd[1]);
            getprogramme(path, left);

        }
        close(fd[0]);                  
        close(fd[1]);                
        waitpid(-1, NULL, 0);               
        waitpid(-1, NULL, 0);
    }
}
