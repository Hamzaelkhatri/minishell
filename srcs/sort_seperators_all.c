/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_seperators_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:47:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 12:29:40 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *define_each1_02(t_list_cmd *lst, char *string, char *red,t_shell *sh) {
  t_all *new1;
  char **tmp;
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  tmp = shell_space_split(string,sh);
  int i = 0;
  if (strcmp(tmp[0], "echo") == 0 && strcmp(tmp[1], "-n") == 0) {
    use.cmd = concat_space(tmp[1], tmp[0]);
    use.arg = concat(tmp, 2);
  } else {
    use.cmd = ft_strdup(tmp[0]);
    use.arg = concat(tmp, 1);
  }
  new1 = s_cmd_details(use.cmd, use.arg, red);
  add_all(&lst->pipe->all, new1);
  lst = red_sort_02(lst, use.cmd, use.arg, red,sh);
  return (lst);
}

t_list_cmd *red_sort_02(t_list_cmd *lst, char *cmd, char *arg, char *red,t_shell *sh) {
  char **free_sp;
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  free_sp = shell_space_split(red,sh);
  while (free_sp[use.i] != NULL) {
    if (quote_bfr_red(free_sp[use.i]) == 1) {
      // puts("redirection is an argument");
      use.arg = ft_strjoin((free_sp)[use.i], " ");
      use.arg1 = concat_space(use.arg, use.arg1);
      use.i++;
    }
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
      lst->pipe->all = all_conditions(lst->pipe->all, free_sp, &use.i);
    else {
      use.arg = ft_strjoin((free_sp)[use.i], " ");
      use.arg1 = concat_space(use.arg, use.arg1);
      use.i++;
    }
  }
  lst->pipe->all =
      update_all(cmd, concat_space(use.arg1, arg), lst->pipe->all->red);
  return (lst);
}
t_list_cmd *sort_all_3(t_list_cmd *lst,t_shell *sh) {
  t_list_cmd *tmp;
  char *string;
  char **free_sp;
  char *cmd;
  char *arg;
  t_all *new1;
  // string = ft_strdup(lst->pipe->str_pipe);
  free_sp = shell_space_split(lst->pipe->str_pipe,sh);
  cmd = free_sp[0];
  if (strcmp(cmd, "echo") == 0 && strcmp(free_sp[1], "-n") == 0) {
    cmd = ft_str_join(cmd, " ", free_sp[1]);
    arg = concat(free_sp, 2);
  } else
    arg = concat(free_sp, 1);
  // puts(arg);
  new1 = s_cmd_details1(cmd, arg);
  add_all(&lst->pipe->all, new1);
  return (lst);
}

