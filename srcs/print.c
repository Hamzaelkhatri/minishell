/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zainabdnayagmail.com <zainabdnayagmail.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:02:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 01:55:21 by zainabdnaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    // if (pipe_e(lst->cmd) == 1) {
    //   while (lst->pipe) {

    //     printf("lst->pipe : {%s}\n", lst->pipe->str_pipe);
    //     lst->pipe = lst->pipe->next;
    //   }
    // } else {
    //   if (pipe_e(lst->cmd) == 1)
    //     lst = lst->next;
    printf("lst->cmd : {%s}\n", lst->cmd);
    // }

    lst = lst->next;
  }
}
void print_all(t_list_cmd *lst, t_shell *sh) {

  while (lst != NULL) {
    if (pipe_e(lst->cmd, sh) == 1) {
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