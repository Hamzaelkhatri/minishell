/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_modify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:18:59 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 12:49:02 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *simple_cmd(t_list_cmd *lst, char **simple_cmd)
{
  int i;
  t_list_cmd *new;

  i = 0;
  while (simple_cmd[i] != NULL)
  {
    new = creat_node(simple_cmd[i]);
    add_cmd(&lst, new);
    i++;
  }
  return (lst);
}
t_all *s_cmd_details1(char *s1, char *s2)
{
  int i;
  t_all *all;

  i = 0;
  all = malloc(sizeof(t_all));
  all->command = no_quote(s1);
  all->argument = no_quote(s2);
  all->redirection = NULL;
  all->red = NULL;
  all->next = NULL;
  return (all);
}
t_all *s_cmd_details2(char *s1, char *s2, t_redirection *red)
{
  int i;
  t_all *all;

  i = 0;
  all = malloc(sizeof(t_all));
  all->command = no_quote(s1);
  all->argument = no_quote(s2);
  all->red = red;
  add_red(&all->red, red);
  all->next = NULL;
  return (all);
}
t_list_cmd *link_list(t_list_cmd *lst, t_shell *sh)
{

  t_list_cmd *list1;
  char **tmp;
  t_pipe *new;
  int i;

  i = 0;
  list1 = lst;
  while (lst != NULL)
  {

    if (pipe_e(lst->cmd, sh) == 1)
    {
      i = 0;
      tmp = ft_minishell_split(lst->cmd, '|', sh);
      while (tmp[i] != NULL)
      {
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