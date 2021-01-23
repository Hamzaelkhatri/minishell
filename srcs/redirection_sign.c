/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_sign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:33:08 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 15:21:06 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *seperat_red(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * 2)))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<') {
      res[0] = tmp[i];
      res[1] = '\0';
      break;
    } else if ((tmp[i] == '>' && tmp[i + 1] == '>')) {
      res = ft_strdup(">>");
      break;
    } else {
      i++;
    }
  }
  return ((res));
}