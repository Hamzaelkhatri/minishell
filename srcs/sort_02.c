/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:07:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/08 10:11:50 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *define_each1_01(t_list_cmd *lst, char *string, char *red) {
  t_all *new1;
  char **tmp;
  t_use *use;
  tmp = ft_space_split(string);
  use->cmd = ft_strdup(tmp[0]);
  if (strcmp(use->cmd, "echo") == 0 && strcmp(use->arg, "-n") == 0) {
    use->cmd = ft_str_join(use->cmd, " ", tmp[1]);
    use->arg = concat(tmp, 2);
  } else
    use->arg = concat(tmp, 1);
  new1 = s_cmd_details(use->cmd, use->arg, red);
  add_all(&lst->all, new1);
  lst = redirection_sort(lst, use->cmd, use->arg, red);
  return (lst);
}

t_list_cmd *redirection_sort(t_list_cmd *lst, char *cmd, char *arg, char *red) {
  char **free_sp;
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  free_sp = ft_space_split(red);
  while (free_sp[use.i] != NULL) {
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
      lst->all = all_conditions(lst->all, free_sp, &use.i);
    else {
      use.arg = ft_strjoin((free_sp)[use.i], " ");
      use.arg1 = concat_1(use.arg, use.arg1);
      use.i++;
    }
    lst->all = update_all(cmd, concat_1(use.arg1, arg), lst->all->red);
  }
  return (lst);
}
