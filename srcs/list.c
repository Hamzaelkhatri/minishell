/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:28:46 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/25 14:45:28 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

t_list_cmd *creat_node(char *content)
{
  t_list_cmd *lst;

  lst = malloc(sizeof(t_list_cmd));
  lst->cmd = content;
  lst->sh_arg = NULL;
  lst->sh_cmd = NULL;
  lst->next = NULL;
  // lst->previous = NULL;
  return (lst);
}

void add_cmd(t_list_cmd **head, t_list_cmd *new_cmd)
{
  t_list_cmd *new;

  if (!head || !new_cmd)
    return;
  new = *head;
  if (new)
  {
    while (new->next)
      new = new->next;
    new->next = new_cmd;
  }
  else
    *head = new_cmd;
}

t_pipe *creat_node_p(char *content)
{
  t_pipe *lst;
  lst = malloc(sizeof(t_pipe));
  lst->str_pipe = content;
  lst->next = NULL;
  return (lst);
}

void add_pipe_list(t_pipe **head, t_pipe *new_cmd)
{
  t_pipe *new;
  if (!head || !new_cmd)
    return;
  new = *head;
  if (new)
  {
    while (new->next)
      new = new->next;
    new->next = new_cmd;
  }
  else
    *head = new_cmd;
}

void print(t_list_cmd *lst, t_shell *sh)
{
  int i;

  i = 0;
  int j = 0;
  printf("\n ************ $$one seperator$$ *************\n");
  printf("for node %d |==>{ %s }\n", i, lst->cmd);
  printf("in node %i this cmd : %s\n", 0, lst->sh_cmd);
  printf("in node %i this is arg : %s\n", 1, lst->sh_arg);
  printf("\n ************ $$one seperator$$ *************\n");
}

void print_nested_lklist(t_list_cmd *lst, t_shell *sh)
{
  int i;

  i = 0;
  int j = 0;

  while (lst)
  {
    j = 0;
    print(lst, sh);
    while (lst->pipe)
    {
      printf("************ $$ PIPE & comma $$ *************\n");
      printf("\n **I m in**\n");
      printf("BIG NODE : %d |==>{ %s }In list_pipe for node {%i} |==>|%s| \n",
             i, lst->cmd, j, lst->pipe->str_pipe);
      printf("==>LSt node %i this cmd : %s\n", 0, lst->pipe->sh_p_cmd);
      printf("==>Lst node %i this is arg : %s\n", 1, lst->pipe->sh_p_arg);
      j++;
      lst->pipe = lst->pipe->next;
      printf("************ $$ PIPE & comma$$ *************\n");
    }
    i++;
    lst = lst->next;
  }
}