/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:48:56 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/25 14:41:49 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void seperat_with_pipe(t_list_cmd *lst, t_shell *sh) {
  int i;
  t_pipe *new;
  char **tmp;

  tmp = NULL;

  while (lst != NULL) {
    i = 0;
    // printf(">>>%s<<<\n", lst->cmd);
    // ft_check_pipe(lst->cmd, sh);
    // ft_check_comma(lst->cmd, sh);
    tmp = ft_split(lst->cmd, '|');
    while (tmp[i] != NULL)
    {
      // printf("\n|>%s|<\n", tmp[i]);
      tmp[i] = ft_strtrim(tmp[i], " ");
      new = creat_node_p(tmp[i]);
      add_pipe_list(&(lst->pipe), new);
      i++;
    }
    lst = lst->next;
  }
}

t_list_cmd *pipe_define_each(t_list_cmd *lst, t_shell *sh, char **env) {
  char **tmp;
  t_pipe *p;

  while (lst != NULL) {
    p = lst->pipe;
    tmp = NULL;
    while (lst->pipe) {
      tmp = ft_space_split(lst->pipe->str_pipe);
      lst->pipe->sh_p_cmd = tmp[0];
      lst->pipe->sh_p_arg = tmp[1];
      lst->pipe = lst->pipe->next;
    }
    lst->pipe = p;
    lst = lst->next;
  }
  return (lst);
}