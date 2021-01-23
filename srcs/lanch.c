/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lanch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:06:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 12:48:21 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    lanch_cmd(char *line)
{
    pid_t pid;
    // pid_t wpid;
    char   *binarypath = "/bin/bash";
    char *const argv[]  = { binarypath, "-c", line, 0} ;


    pid = fork();
    if (pid == 0)
        {
            if(!(execve(binarypath, argv, NULL)))
                      printf("Error: %s\n", strerror(errno));
        }
}