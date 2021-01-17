/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/09 11:25:10 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// https://guide.bash.academy/commands/

t_list_cmd *simple_cmd(t_list_cmd *lst, char **simple_cmd) {
  int i;
  t_list_cmd *new;

  i = 0;
  while (simple_cmd[i] != NULL) {
    simple_cmd[i] = ft_strtrim(simple_cmd[i], " ");
    new = creat_node(simple_cmd[i]);
    add_cmd(&lst, new);
    i++;
  }
  return (lst);
}

/**************************************/
// had fonction ghit zayda 7eta ldb!!!!!
// t_list_cmd *define_each1(t_list_cmd *lst) {
//   char **tmp;
//   t_shell *sh;
//   int i;
//   int j;

//   i = 0;
//   j = 0;
//   tmp = NULL;
//   t_list_cmd *lst1;
//   lst1 = lst;

//   while (lst != NULL) {
//     tmp = ft_space_split(lst->cmd);
//     lst = lst->next;
//   }
//   lst1 = lst;
//   return (lst);
// }
/**************************************/

t_list_cmd *define_each(t_list_cmd *lst) {
  char *string;
  char *red;
  t_all *new1;
  char **tmp;
  t_use use;
  if (search(lst->cmd) == 1) {
    string = is_befor_redirection(lst->cmd);
    red = is_after_redirection(lst->cmd);
    if (string == NULL) {
      new1 = s_cmd_details(NULL, NULL, red);
      add_all(&lst->all, new1);
      tmp = ft_space_split(red);
      lst = sort_all_2(lst, lst->all, red, tmp);
    } else {
      lst = define_each1_01(lst, string, red);
    }
  } else
    lst = sort_all_1(lst);

  return (lst);
}

t_list_cmd *handle_line(t_shell *sh, t_read *rd, t_list_cmd *lst, char **env) {
  int i;
  t_pipe *pipe;

  i = 0;
  lst = NULL;
  if (check_one(rd->line, sh) == 0) {
    lst = creat_node(rd->line);
    define_each(lst);
  } else if (check_one(rd->line, sh) == 1) {
    sh->simple_cmd = ft_split(rd->line, '|');
    lst = simple_cmd(lst, sh->simple_cmd);
  } else if (check_one(rd->line, sh) == 2) {
    sh->simple_cmd = ft_split(rd->line, ';');
    lst = simple_cmd(lst, sh->simple_cmd);
  } else if (check_one(rd->line, sh) == 3) {
    sh->simple_cmd = ft_split(rd->line, ';');
    lst = simple_cmd(lst, sh->simple_cmd);
  }
  if (check_one(rd->line, sh) != 0)
    cmd_details(lst);
  return (lst);
}