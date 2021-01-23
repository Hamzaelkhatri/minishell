/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:40:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/22 15:27:05 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int search(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if ((str[i] == '\'' || str[i] == '\"') &&
        (str[i + 1] == '<' || str[i + 1] == '>' ||
         (str[i + 1] == '>' && str[i + 2] == '>')))
      return (0);
    if ((str[i] == '>' || str[i] == '<' ||
         (str[i] == '>' && str[i + 1] == '>')) &&
        (str[i + 1] != '\0' || str[i + 1] != '\n'))
      return (1);
    i++;
  }
  return (0);
}

char **search_4_red(char *line) {
  int i;
  int j;
  char **tmp;
  char **str;

  i = 0;
  j = 0;
  str = malloc(sizeof(char) * 100);
  tmp = ft_split(line, ' ');
  while (tmp[i] != NULL) {
    if (search(tmp[i]) == 1)
      str[j++] = ft_strdup(tmp[i]);
    i++;
  }
  return (str);
}