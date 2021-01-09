/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:36:46 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/09 10:22:48 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

t_all *s_cmd_details1(char *s1, char *s2) {
  int i;
  t_all *all;

  i = 0;
  all = malloc(sizeof(t_all));
  all->command = s1;
  all->argument = s2;
  all->redirection = NULL;
  all->red = NULL;
  all->next = NULL;
  return (all);
}
t_all *s_cmd_details2(char *s1, char *s2, t_redirection *red) {
  int i;
  t_all *all;

  i = 0;
  all = malloc(sizeof(t_all));
  all->command = s1;
  all->argument = s2;
  all->red = red;
  add_red(&all->red, red);
  all->next = NULL;
  return (all);
}

t_list_cmd *sort_all_1(t_list_cmd *lst) {
  t_list_cmd *tmp;
  char *string;
  char **free_sp;
  char *cmd;
  char *arg;
  t_all *new1;
  string = ft_strdup(lst->cmd);
  free_sp = ft_space_split(string);
  cmd = free_sp[0];
  if (strcmp(cmd, "echo") == 0 && strcmp(free_sp[1], "-n") == 0) {
    cmd = ft_str_join(cmd, " ", free_sp[1]);
    arg = concat(free_sp, 2);
  } else
    arg = concat(free_sp, 1);
  new1 = s_cmd_details1(cmd, arg);
  add_all(&lst->all, new1);
  return (lst);
}

t_list_cmd *sort_all_3(t_list_cmd *lst) {
  t_list_cmd *tmp;
  char *string;
  char **free_sp;
  char *cmd;
  char *arg;
  t_all *new1;
  string = ft_strdup(lst->pipe->str_pipe);
  free_sp = ft_space_split(string);
  cmd = free_sp[0];
  if (strcmp(cmd, "echo") == 0 && strcmp(free_sp[1], "-n") == 0) {
    cmd = ft_str_join(cmd, " ", free_sp[1]);
    arg = concat(free_sp, 2);
  } else
    arg = concat(free_sp, 1);
  new1 = s_cmd_details1(cmd, arg);
  add_all(&lst->pipe->all, new1);
  return (lst);
}
