/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/07 12:40:56 by zdnaya           ###   ########.fr       */
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
  define_each(lst);
  return (lst);
}

t_list_cmd *define_each(t_list_cmd *lst) {
  char **tmp;
  t_shell *sh;
  int i;
  int j;

  i = 0;
  j = 0;
  tmp = NULL;
  t_list_cmd *lst1;
  lst1 = lst;

  while (lst != NULL) {
    tmp = ft_space_split(lst->cmd);
    lst = lst->next;
  }
  lst1 = lst;
  return (lst);
}

t_list_cmd *define_each1(char *line) {
  char *string;
  char *red;
  t_list_cmd *lst;
  t_all *new1;

  lst = creat_node(line);
  if (search(lst->cmd) == 1) {
    string = is_befor_redirection(lst->cmd);
    red = is_after_redirection(lst->cmd);
    if (string == NULL) {
      new1 = s_cmd_details(NULL, NULL, red);
      add_all(&lst->all, new1);
      lst = sort_all_2(lst, lst->all, red);
    }
  } else {
    lst = sort_all_1(lst);
  }

  return (lst);
}

t_list_cmd *handle_line(t_shell *sh, t_read *rd, t_list_cmd *lst, char **env) {
  int i;
  t_pipe *pipe;

  i = 0;
  lst = NULL;
  if (check_one(rd->line, sh) == 0) {
    lst = define_each1(rd->line);
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