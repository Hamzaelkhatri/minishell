/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:48:56 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 12:13:33 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pipe_e(char *line, t_shell *sh) {
  int i;

  i = 0;
  char c;
  c = quote_char(line, sh);
  while (line[i]) {
    if (line[i] == 34 || line[i] == 39)
      i = escape_from_until(line, i, c) + 1;
    if (line[i] == '|')
      return (1);
    i++;
  }
  return (0);
}

t_pipe *both(t_list_cmd *lst, t_shell *sh) {
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
  if (pipe_e(lst->cmd, sh) == 1) {

    tmp = ft_minishell_split(lst->cmd, '|', sh);
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