/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:44:38 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/09 11:34:23 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all *s_cmd_details(char *s1, char *s2, char *s3) {
  int i;
  t_all *all;

  i = 0;
  all = malloc(sizeof(t_all));
  all->command = s1;
  all->argument = s2;
  all->redirection = s3;
  all->next = NULL;
  return (all);
}

char **check_each_node(char *line) {

  char **tmp;
  char **tmp1;
  char **tmp2;

  line = befor_direction(line);
  tmp = ft_space_split(line);

  return (tmp);
}
t_list_cmd *link_list(t_list_cmd *lst) {

  t_list_cmd *list1;
  t_shell *sh;
  char **tmp;
  t_pipe *new;
  int i;

  i = 0;
  list1 = lst;
  while (lst != NULL) {
    if (pipe_e(lst->cmd) == 1) {
      i = 0;
      tmp = ft_split(lst->cmd, '|');
      while (tmp[i] != NULL) {
        tmp[i] = ft_strtrim(tmp[i], " ");
        new = creat_node_p(tmp[i]);
        add_pipe_list(&(lst->pipe), new);
        i++;
      }
    }

    lst = lst->next;
  }
  lst = list1;
  return (lst);
}

void part_two(t_list_cmd *lst) {
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
}