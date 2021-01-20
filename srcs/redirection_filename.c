/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:34:31 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 17:34:52 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *seperat_file_name(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * (strlen(tmp)))))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<')
      i++;
    else if ((tmp[i] == '>' && tmp[i + 1] == '>'))
      i = i + 2;
    else {
      res[j] = tmp[i];
      j++;
      i++;
    }
  }
  res[j] = '\0';
  return (no_quote(res));
}

