/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:07:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/07 18:46:48 by zdnaya           ###   ########.fr       */
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

  return (lst);
}