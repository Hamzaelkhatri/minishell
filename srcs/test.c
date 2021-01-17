/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:48:51 by ahaddad           #+#    #+#             */
/*   Updated: 2021/01/09 17:44:08 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void pipes_cmds(t_path *path, t_list_cmd *lst, t_cmd *cmd1, int s)
{
    int fd[2];
    int _fd[2];

    int i;
    pid_t pid;
    t_all *list1;
    char *cmd;
    i = 0;

    list1 = lst->all;

    printf("\n%d\n",s);
    while (lst->all != NULL)
    {
        pipe(fd);
        ch_comma_buil(cmd1, lst->all->command);
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
    // printf("\n%d\n",cmd1->env);
            char *binaryPath = "/bin/bash";
            if (lst->all->argument)
                cmd = ft_str_join(lst->all->command, " ", lst->all->argument);
            else
                cmd = lst->all->command;
            char *const args[] = {binaryPath, "-c", cmd, NULL};
            if (cmd1->pwd == 1)
            {
                print_working_directory(path);
            }
            else if (cmd1->export == 1)
                export_cmd(lst->all->argument, path->env->fullenv);
            else if (cmd1->cd == 1)
                cd_cmd(lst->all->argument, path);
            else if (cmd1->echo == 1)
            {
            }
            else if (cmd1->env == 1)
            {
                puts("here");
                show_env(path->env->fullenv);
            }
            else if (cmd1->exit == 1)
                exit(0);
            else if (cmd1->unset == 1)
                unset_cmd(lst->all->argument, path);
            else
            {
                if (execve(binaryPath, args, NULL) < 0)
                    // printf("dertha bel execve");
                    // getprogramme(path, lst->all->command);
                    exit(1);
            }
            exit(0);
        }
        else
        {
            close(fd[1]);
            _fd[0] = fd[0];
            _fd[1] = fd[1];
            lst->all = lst->all->next;
        }
        i++;
    }
    lst->all = list1;
    wait(0);
}