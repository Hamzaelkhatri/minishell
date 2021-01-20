/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:56:08 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 12:22:13 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void part_two(t_list_cmd *lst, t_shell *sh) {
  char *string;
  char *red;
  t_all *new1;
  char **tmp;
  t_use use;

  if (search(lst->cmd) == 1) {
    string = is_befor_redirection(lst->cmd,sh);
    red = is_after_redirection(lst->cmd,sh,string);
    if (string == NULL) {
      new1 = s_cmd_details(NULL, NULL, red);
      add_all(&lst->all, new1);
      tmp = shell_space_split(red, sh);
      lst = sort_all_2(lst, lst->all, tmp);
    } else {
      lst = define_each1_01(lst, string, red, sh);
    }
  } else {
    lst = sort_all_1(lst, sh);
  }
}