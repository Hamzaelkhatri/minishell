/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:20:01 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 16:58:01 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *define_each(t_list_cmd *lst, t_shell *sh)
{

  char *string;
  char *red;
  t_all *new1;
  char **tmp;
  t_use use;
  int i = 0;

  if (search(lst->cmd) == 1)
  {

    string = is_befor_redirection(lst->cmd, sh);
    red = is_after_redirection(lst->cmd, sh, string);
    if (string == NULL)
    {
      new1 = s_cmd_details(NULL, NULL, red);
      add_all(&lst->all, new1);
      tmp = shell_space_split(red);
      lst = sort_all_2(lst, lst->all, tmp);
    }
    else
    {
      lst = define_each1_01(lst, string, red, sh);
    }
  }
  else
  {
    lst = sort_all_1(lst, sh);
  }

  return (lst);
}

t_list_cmd *sort_all_2(t_list_cmd *lst, t_all *all, char **free_sp)
{
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  while (free_sp[use.i] != NULL)
  {
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
    {
      all = all_conditions(all, free_sp, &use.i);
    }
    else
    {
      condition_3(&use, &free_sp);
    }
  }
  lst->all = update_all(use.cmd2, use.arg1, all->red);
  return (lst);
}

t_list_cmd *define_each1_01(t_list_cmd *lst, char *string, char *red,
                            t_shell *sh)
{
  t_all *new1;
  char **tmp;
  char **tmp1;
  t_use use;
  
  ft_bzero(&use, sizeof(t_use));
  tmp = shell_space_split(string);
  if (ft_strcmp(tmp[0], "echo") == 0 && tmp[1] != NULL && ft_strcmp(tmp[1], "-n") == 0)
  {
    use.cmd = concat_space(tmp[1], tmp[0]);
    use.arg = concat(tmp, 2);
  }
  else
  {
    use.cmd = tmp[0];
    use.arg = concat(tmp, 1);
  }

  new1 = s_cmd_details(no_quote(use.cmd), no_quote(use.arg), red);

  add_all(&lst->all, new1);
  tmp1 = shell_space_split(red);
  lst = redirection_sort(lst, use.cmd, use.arg, tmp1);
  return (lst);
}

t_list_cmd *sort_all_1(t_list_cmd *lst, t_shell *sh)
{
  t_list_cmd *tmp;
  char *string;
  char **free_sp;
  char *cmd;
  char *arg;
  t_all *new1;
  string = ft_strdup(lst->cmd);

  free_sp = shell_space_split(string);
  cmd = free_sp[0];
  if (ft_strcmp(cmd, "echo") == 0 && free_sp[1] != NULL && ft_strcmp(free_sp[1], "-n") == 0)
  {
    cmd = ft_str_join(cmd, " ", free_sp[1]);
    arg = concat(free_sp, 2);
  }
  else
    arg = concat(free_sp, 1);
  new1 = s_cmd_details1(cmd, arg);
  add_all(&lst->all, new1);
  return (lst);
}

t_list_cmd *redirection_sort(t_list_cmd *lst, char *cmd, char *arg,
                             char **free_sp)
{
  int i = 0;
  t_use use;
  ft_bzero(&use, sizeof(t_use));
  while (free_sp[use.i] != NULL)
  {
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
    {
      lst->all = all_conditions(lst->all, free_sp, &use.i);
    }
    else
    {
      use.arg = ft_strjoin((free_sp)[use.i], " ");
      use.arg1 = concat_space(use.arg, use.arg1);
      use.i++;
    }
  }
  lst->all = update_all(cmd, concat_space(use.arg1, arg), lst->all->red);
  return (lst);
}
