/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:05:19 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 14:37:13 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all *s_cmd_details(char *s1, char *s2, char *s3) {
  t_all *all;

  // puts(s1);
  // puts(s2);
  all = malloc(sizeof(t_all));
  all->command = s1;
  all->argument = s2;
  all->redirection = s3;
  all->next = NULL;
  return (all);
}

t_list_cmd *creat_node(char *content) {
  t_list_cmd *lst;

  lst = malloc(sizeof(t_list_cmd));
  lst->cmd = content;
  lst->next = NULL;
  return (lst);
}

t_redirection *creat_node_r(char *content, char *content1) {
  t_redirection *red;
    // puts(content);
    // puts(content1);
  red = malloc(sizeof(t_redirection));
  red->sign = no_quote(content);
  red->next = malloc(sizeof(t_redirection));
  red->next->file_name = no_quote(content1);
  red->next->next = NULL;
  return (red);
}
t_pipe *creat_node_p(char *content) {
  t_pipe *lst;
  lst = malloc(sizeof(t_pipe));
  lst->str_pipe = content;
  lst->next = NULL;
  return (lst);
}
t_all *update_all(char *cmd, char *arg, t_redirection *red) {
  t_all *new_all;

  new_all = malloc(sizeof(t_all));
  new_all->command = no_quote(cmd);
  new_all->argument = no_quote(arg);
  new_all->red = red;
  new_all->next = NULL;
  return (new_all);
}

