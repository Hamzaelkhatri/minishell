/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:30:13 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 12:49:17 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ch_comma_buil(t_cmd *cmd, char *comnd)
{
  cmd->cd = 0;
  cmd->pwd = 0;
  cmd->unset = 0;
  cmd->env = 0;
  cmd->export = 0;
  cmd->echo = 0;
  cmd->exit = 0;
  cmd->redir = 0;
  comnd = ft_strtrim(comnd, "\n");
  if (ft_strcmp(comnd, "pwd") == 0)
    cmd->pwd = 1;
  else if (ft_strcmp(comnd, "cd") == 0)
    cmd->cd = 1;
  else if (ft_strcmp(comnd, "unset") == 0)
    cmd->unset = 1;
  else if (ft_strcmp(comnd, "env") == 0)
    cmd->env = 1;
  else if (ft_strcmp(comnd, "export") == 0)
    cmd->export = 1;
  else if (ft_strcmp(comnd, "echo") == 0)
    cmd->echo = 1;
  else if (ft_strcmp(comnd, "exit") == 0)
    cmd->exit = 1;
  else if (search(comnd))
    cmd->redir = 1;
}

void call_getprg(t_list_cmd *lst, t_path *path, t_cmd *cmd)
{
  t_list_cmd *tmp;
  t_all *tmp1;
  char *s;
  char *p;

  tmp = lst;
  while (lst != NULL)
  {
    tmp1 = lst->all;
    while (lst->all != NULL)
    {

      ch_comma_buil(cmd, lst->all->command);
      if (search(lst->cmd))
        shift_extra(lst->all->red->next->file_name, lst->all->red->sign, path,
                    lst->all);
      else if (cmd->pwd == 1)
      {
        print_working_directory(path);
      }
      else if (cmd->export == 1)
      {
        export_cmd(lst->all->argument, path->env->fullenv);
      }
      else if (cmd->cd == 1)
        cd_cmd(lst->all->argument, path);
      else if (cmd->echo == 1)
      {
      }
      else if (cmd->env == 1)
      {
        show_env(path->env->fullenv);
      }
      else if (cmd->exit == 1)
        exit(0);
      else if (cmd->unset == 1)
        unset_cmd(lst->all->argument, path);
      else
      {
        if (lst->all->argument)
        {
          lst->all->command = ft_strjoin(lst->all->command, " ");
          lst->all->command = ft_strjoin(lst->all->command, lst->all->argument);
        }
        getprogramme(path, lst->all->command);
      }
      lst->all = lst->all->next;
    }
    lst->all = tmp1;
    lst = lst->next;
  }
  lst = tmp;
}

void call_pipe(t_list_cmd *lst, t_path *path, t_shell *sh, t_cmd *cmd)
{
  t_list_cmd *list1;
  t_pipe *pipe;
  t_all *tmp1;

  list1 = lst;
  while (lst != NULL)
  {
    if (pipe_e(lst->cmd, sh) == 1)
    {
      pipes_cmd(path, lst, cmd);
      wait(0);
    }
    else
    {
      call_getprg(lst, path, cmd);
    }
    lst = lst->next;
  }
  lst = list1;
}
