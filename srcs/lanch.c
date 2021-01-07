/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lanch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:06:18 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/17 12:14:50 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

    //   int execve(const char *pathname, char *const argv[],
    //               char *const envp[]);

//       The envp array must be terminated by a NULL pointer.
///The argv array must be terminated by a NULL pointer.
//-c option: https://unix.stackexchange.com/questions/144514/add-arguments-to-bash-c

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