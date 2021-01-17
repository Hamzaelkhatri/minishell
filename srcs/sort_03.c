/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:12:37 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/09 11:37:42 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *define_each1_02(t_list_cmd *lst, char *string, char *red) {
  t_all *new1;
  char **tmp;
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  //   puts("here");

  tmp = ft_space_split(string);
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
  lst = red_sort_02(lst, use.cmd, use.arg, red);
  return (lst);
}

t_list_cmd *red_sort_02(t_list_cmd *lst, char *cmd, char *arg, char *red) {
  char **free_sp;
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  free_sp = ft_space_split(red);
  while (free_sp[use.i] != NULL) {
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
