/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:18:37 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/26 17:20:31 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_check_comma(char *line, t_shell *sh) {
  int i;

  i = 0;
  sh->comma = 0;
  while (line[i]) {
    if (line[i] == ';') {
      sh->comma = 1;
    }
    i++;
  }
}
void ft_check_pipe(char *line, t_shell *sh) {
  int i;

  i = 0;
  // printf(" im here");
  sh->pipe = 0;
  while (line[i]) {
    if (line[i] == '|') {
      sh->pipe = 1;
    }
    i++;
  }
}

int check_one(char *line, t_shell *sh) {

  ft_check_comma(line, sh);
  ft_check_pipe(line, sh);
  if (sh->pipe == 1 && sh->comma == 0)
    return (1);
  else if (sh->pipe == 0 && sh->comma == 1)
    return (2);
  else if (sh->pipe == 1 && sh->comma == 1)
    return (3);
  else
    return (0);
}


int check_revers_check(char caract,char next_char,char one,char two)
{
  if ((caract == one  && next_char == two) || (caract == two && next_char == one))
      return(1);
      else
        return(0);
}


int count_array(char **tmp)
{
  int i;

  i = 0;
  while(tmp[i] != NULL)
    i++;
  return(i);
}