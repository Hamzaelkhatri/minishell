/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 10:32:55 by ahaddad           #+#    #+#             */
/*   Updated: 2021/01/23 12:50:49 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int lstsize(t_list_cmd *lst)
{
  t_pipe *list1;
  t_list_cmd *lst1;
  t_all *all;
  int i;

  i = 0;
  list1 = lst->pipe;
  while (lst->pipe != NULL)
  {
    all = lst->pipe->all;
    while (lst->pipe->all != NULL)
    {
      i++;
      lst->pipe->all = lst->pipe->all->next;
    }
    lst->pipe->all = all;
    lst->pipe = lst->pipe->next;
  }
  lst->pipe = list1;

  return (i);
}

int lstsize_1(t_list_cmd *lst)
{
  t_list_cmd *list1;
  t_all *all;
  int i;

  i = 0;
  list1 = lst;
  while (lst != NULL)
  {
    all = lst->all;
    while (lst->all != NULL)
    {
      i++;
      lst->all = lst->all->next;
    }
    lst->all = all;
    lst = lst->next;
  }
  lst = list1;
  return (i);
}

void pipes_cmd1(t_path *path, t_list_cmd *lst, t_cmd *cmd1)
{
  int fd[2];
  int _fd[2];

  int i;
  pid_t pid;
  t_list_cmd *list1;
  t_pipe *tmp1;
  char *cmd;
  i = 0;

  list1 = lst;
  int s = lstsize_1(lst);
  while (lst != NULL)
  {
    while (lst->all)
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
          show_env(path->env->fullenv);
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
    lst = lst->next;
  }
  lst = list1;
  wait(0);
}

void pipes_cmd(t_path *path, t_list_cmd *lst, t_cmd *cmd1)
{
  int fd[2];
  int _fd[2];

  int i;
  pid_t pid;
  t_pipe *tmp1;
  t_list_cmd *lst1;
  t_all *all;
  char *cmd;
  i = 0;
  int s = lstsize(lst);
  int j = 0;
  while (lst->pipe != NULL)
  {
    all = lst->pipe->all;
    while (lst->pipe->all != NULL)
    {
      pipe(fd);
      ch_comma_buil(cmd1, lst->pipe->all->command);
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
        if (lst->pipe->all->argument)
          cmd = ft_str_join(lst->pipe->all->command, " ",
                            lst->pipe->all->argument);
        else
          cmd = lst->pipe->all->command;
        char *const args[] = {binaryPath, "-c", cmd, NULL};
        if (cmd1->pwd == 1)
        {
          print_working_directory(path);
        }
        else if (cmd1->export == 1)
          export_cmd(lst->pipe->all->argument, path->env->fullenv);
        else if (cmd1->cd == 1)
          cd_cmd(lst->pipe->all->argument, path);
        else if (cmd1->echo == 1)
        {
        }
        else if (cmd1->env == 1)
        {
          // puts("here");
         show_env(path->env->fullenv);
        }else if (cmd1->exit == 1)
          exit(0);
        else if (cmd1->unset == 1)
          unset_cmd(lst->pipe->all->argument, path);
        else if (execve(binaryPath, args, path->env->fullenv) < 0)
          exit(1);
        exit(0);
      }
      else
      {
        close(fd[1]);
        _fd[0] = fd[0];
        _fd[1] = fd[1];
        lst->pipe->all = lst->pipe->all->next;
      }
      i++;
    }
    lst->pipe->all = all;
    lst->pipe = lst->pipe->next;
  }
  lst->pipe = tmp1;
  wait(0);
}
