/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:36:46 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/07 12:57:08 by zdnaya           ###   ########.fr       */
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

char *seperat_red(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * 2)))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<') {
      res[0] = tmp[i];
      res[1] = '\0';
      break;
    } else if ((tmp[i] == '>' && tmp[i + 1] == '>')) {
      res = ft_strdup(">>");
      break;
    } else {
      i++;
    }
  }
  return (res);
}
char *seperat_file_name(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * (strlen(tmp)))))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<')
      i++;
    else if ((tmp[i] == '>' && tmp[i + 1] == '>'))
      i = i + 2;
    else {
      res[j] = tmp[i];
      j++;
      i++;
    }
  }
  res[j] = '\0';
  return (res);
}

int condition_1(char **free_sp, int i) {
  if (check_redirection(free_sp[i]) != 0 && free_sp[i + 1] != NULL &&
      (strcmp(free_sp[i], ">>") == 0 || strcmp(free_sp[i], ">") == 0 ||
       strcmp(free_sp[i], "<") == 0))
    return (1);
  else
    return (0);
}
int condition_2(char **free_sp, int i) {
  if (check_redirection(free_sp[i]) != 0 &&
      (strcmp(free_sp[i], ">>") != 0 || strcmp(free_sp[i], ">") != 0 ||
       strcmp(free_sp[i], "<") != 0))
    return (1);
  else
    return (0);
}

t_list_cmd *sort_all_2(t_list_cmd *lst, t_all *all, char *red) {
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  use.free_sp = ft_space_split(red);
  while (use.free_sp[use.i] != NULL) {
    if (condition_1(use.free_sp, use.i) == 1) {
      use.red1 = creat_node_r(use.free_sp[use.i], use.free_sp[use.i + 1]);
      add_red(&all->red, use.red1);
      use.i = use.i + 2;
    } else if (condition_2(use.free_sp, use.i) == 1) {
      use.sign = seperat_red(use.free_sp[use.i]);
      use.file_name = seperat_file_name(use.free_sp[use.i]);
      use.red1 = creat_node_r(use.sign, use.file_name);
      add_red(&all->red, use.red1);
      use.i++;
    } else {
      if (use.cmd_index == 0) {
        use.cmd2 = ft_strdup(use.free_sp[use.i]);
        use.cmd_index = 1;
        use.i++;
      } else {
        use.arg = ft_strjoin(use.free_sp[use.i], " ");
        use.arg1 = concat_1(use.arg, use.arg1);
        use.i++;
      }
    }
    lst->all = update_all(use.cmd2, use.arg1, all->red);
  }
  return (lst);
}