/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:48:56 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/03 10:58:21 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pipe_e(char *line) {
  int i;

  i = 0;
  while (line[i] != '\0') {
    if (line[i] == '|')
      return (1);
    i++;
  }
  return (0);
}

t_pipe *both(t_list_cmd *lst) {
  t_list_cmd *tmp1;
  t_pipe *new;
  t_pipe *pipe;
  t_pipe *tmp2;

  pipe = NULL;
  char **tmp;
  int i;

  i = 0;
  tmp1 = lst;
  int j = 0;
  if (pipe_e(lst->cmd) == 1) {

    tmp = ft_split(lst->cmd, '|');
    i = 0;
    while (tmp[i] != NULL) {
      tmp[i] = ft_strtrim(tmp[i], " ");
      new = creat_node_p(tmp[i]);
      add_pipe_list(&(pipe), new);
      i++;
    }
    j++;
  }
  j = 0;

  return (pipe);
}