/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:56:50 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 12:51:05 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void part_one(t_list_cmd *lst, t_shell *sh)
{
  t_pipe *pipe;
  t_all *all;
  char *string;
  char *str;
  char **tmp;
  char *cmd;
  char *arg;
  char *red;
  t_all *new1;

  pipe = lst->pipe;
  while (lst->pipe != NULL)
  {
    if (search(lst->pipe->str_pipe) == 1)
    {
      string = is_befor_redirection(lst->pipe->str_pipe, sh);
      red = is_after_redirection(lst->pipe->str_pipe, sh, string);
      if (string == NULL)
      {
        new1 = s_cmd_details(NULL, NULL, red);
        add_all(&lst->pipe->all, new1);
        tmp = shell_space_split(red);
        lst = sort_all_2(lst, lst->pipe->all, tmp);
      }
      else
      {

        lst = define_each1_02(lst, string, red, sh);
      }
    }
    else
      lst = sort_all_3(lst, sh);
    lst->pipe = lst->pipe->next;
  }
  lst->pipe = pipe;
}
