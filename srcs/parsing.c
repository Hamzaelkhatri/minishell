/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/22 18:41:35 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *handle_line(t_shell *sh, t_read *rd, t_list_cmd *lst, char **env)
{
  int i;
  t_pipe *pipe;

  i = 0;
  lst = NULL;

  rd->line = ft_strtrim(rd->line, " ");

  if (check_one(rd->line, sh) == 0)
  {
    lst = creat_node(rd->line);
    define_each(lst, sh);
    return (lst);
  } else if (check_one(rd->line, sh) == 1) {
    sh->simple_cmd = ft_minishell_split(rd->line, '|', sh);
    lst = simple_cmd(lst, sh->simple_cmd);
  }
  else if (check_one(rd->line, sh) == 2)
  {
    sh->simple_cmd = ft_minishell_split(rd->line, ';', sh);
    lst = simple_cmd(lst, sh->simple_cmd);

  } else if (check_one(rd->line, sh) == 3) {

    sh->simple_cmd = ft_minishell_split(rd->line, ';', sh);
    lst = simple_cmd(lst, sh->simple_cmd);
  }
  if (check_one(rd->line, sh) != 0)
    comand_details(lst, sh);
  return (lst);
}