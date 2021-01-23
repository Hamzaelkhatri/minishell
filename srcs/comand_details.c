/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/22 18:42:11 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void comand_details(t_list_cmd *lst, t_shell *sh) {

  t_all *new1;
  t_list_cmd *lstt;
  t_pipe *pipes;

  lst = link_list(lst, sh);
  lstt = lst;
  while (lst != NULL) {
    if (pipe_e(lst->cmd, sh) == 1) {
      part_one(lst, sh);

    } else {
      if (pipe_e(lst->cmd, sh) == 1)
        lst = lst->next;

      part_two(lst, sh);

    }
    lst = lst->next;
  }
  lst = lstt;
}
