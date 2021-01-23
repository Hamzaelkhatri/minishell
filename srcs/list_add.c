/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:28:46 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 17:15:30 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_cmd(t_list_cmd **head, t_list_cmd *new_cmd) {
  t_list_cmd *new;

  if (!head || !new_cmd)
    return;
  new = *head;
  if (new) {
    while (new->next)
      new = new->next;
    new->next = new_cmd;
  } else
    *head = new_cmd;
}


void add_pipe_list(t_pipe **head, t_pipe *new_cmd) {
  t_pipe *new;
  if (!head || !new_cmd)
    return;
  new = *head;
  if (new) {
    while (new->next)
      new = new->next;
    new->next = new_cmd;
  } else
    *head = new_cmd;
}

void add_all(t_all **head, t_all *new_cmd) {
  t_all *new;
  if (!head || !new_cmd)
    return;
  new = *head;
  if (new) {
    while (new->next)
      new = new->next;
    new->next = new_cmd;
  } else
    *head = new_cmd;
}

void add_red(t_redirection **head, t_redirection *new_cmd) {
  t_redirection *new;
  if (!head || !new_cmd)
    return;
  new = *head;
  if (new) {
    while (new->next)
      new = new->next;
    new->next = new_cmd;
  } else
    *head = new_cmd;
}
