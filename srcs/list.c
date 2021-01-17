/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:28:46 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/09 11:36:15 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_list_cmd *creat_node(char *content) {
  t_list_cmd *lst;

  lst = malloc(sizeof(t_list_cmd));
  lst->cmd = content;
  lst->next = NULL;
  // lst->previous = NULL;
  return (lst);
}
t_redirection *creat_node_r(char *content, char *content1) {
  t_redirection *red;

  red = malloc(sizeof(t_redirection));
  red->sign = content;
  red->next = malloc(sizeof(t_redirection));
  red->next->file_name = content1;
  red->next->next = NULL;
  return (red);
}
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

t_pipe *creat_node_p(char *content) {
  t_pipe *lst;
  lst = malloc(sizeof(t_pipe));
  lst->str_pipe = content;
  lst->next = NULL;
  return (lst);
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
t_all *update_all(char *cmd, char *arg, t_redirection *red) {
  t_all *new_all;

  new_all = malloc(sizeof(t_all));
  new_all->command = cmd;
  new_all->argument = arg;
  new_all->red = red;
  new_all->next = NULL;
  return (new_all);
}

void print(t_pipe *pipe, t_shell *sh) {

  int j = 0;

  while (pipe != NULL) {
    printf("|>for %d str : %s\n", j, pipe->str_pipe);
    j++;
    pipe = pipe->next;
  }
}

void print_nested_lklist(t_list_cmd *lst) {
  int i;

  i = 0;
  int j = 0;

  while (lst) {
    if (pipe_e(lst->cmd) == 1) {
      while (lst->pipe) {

        printf("lst->pipe : {%s}\n", lst->pipe->str_pipe);
        lst->pipe = lst->pipe->next;
      }
    } else {
      if (pipe_e(lst->cmd) == 1)
        lst = lst->next;
      printf("lst->cmd : {%s}\n", lst->cmd);
    }

    lst = lst->next;
  }
}
void print_all(t_list_cmd *lst) {

  while (lst != NULL) {
    if (pipe_e(lst->cmd) == 1) {
      while (lst->pipe) {
        // puts("here");
        while (lst->pipe->all) {

          printf("************ $$ PIPE & comma$$ *************\n");
          printf("cmd : |%s|\n", lst->pipe->all->command);
          printf("arg : |%s|\n", lst->pipe->all->argument);
          // printf("red : |%s|\n", lst->pipe->all->redirection);
          while (lst->pipe->all->red != NULL) {
            if (lst->pipe->all->red->sign != NULL)
              printf("sign : |%s|\n", lst->pipe->all->red->sign);
            if (lst->pipe->all->red->file_name != NULL)
              printf("file_name : |%s|\n", lst->pipe->all->red->file_name);
            lst->pipe->all->red = lst->pipe->all->red->next;
          }
          printf("/***********************************/\n");
          lst->pipe->all = lst->pipe->all->next;
        }
        lst->pipe = lst->pipe->next;
      }
    } else {
      while (lst->all != NULL) {
        printf("************ $$ comma || Pipe $$ *************\n");
        printf("cmd : |%s|\n", lst->all->command);
        printf("arg : |%s|\n", lst->all->argument);
        // printf("red : |%s|\n", lst->all->redirection);

        while (lst->all->red != NULL) {
          if (lst->all->red->sign != NULL)
            printf("sign : |%s|\n", lst->all->red->sign);
          if (lst->all->red->file_name != NULL)
            printf("file_name : |%s|\n", lst->all->red->file_name);
          lst->all->red = lst->all->red->next;
        }
        printf("/***********************************/\n");
        lst->all = lst->all->next;
      }
    }
    lst = lst->next;
  }
}