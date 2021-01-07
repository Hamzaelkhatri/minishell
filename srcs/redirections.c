/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 12:29:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/06 16:26:06 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int remenber_index(char *line) {
  int i;
  int index;

  i = 0;
  index = 0;
  while (line[i] != '\0') {
    if (line[i] == '<' || line[i] == '>' ||
        (line[i] == '>' && line[i + 1] == '>')) {
      index = i;
      break;
    } else
      i++;
  }
  return (index);
}
char *ft_substring(char *destination, const char *source, int start, int len) {

  while (len > 0) {
    *destination = *(source + start);
    destination++;
    source++;
    len--;
  }
  *destination = '\0';
  return destination;
}

char *is_after_redirection(char *line) {
  char *tmp;
  int index;
  int len;
  int len1;
  int len2;
  int start;
  char *one_part;

  len1 = ft_strlen(line);
  one_part = malloc(sizeof(char) * (len1 + 1));
  tmp = malloc(sizeof(char) * (len1 + 1));
  one_part = is_befor_redirection(line);
  if (one_part == NULL)
    len2 = 0;
  else
    len2 = strlen(one_part);
  start = remenber_index(line);
  len = len1 - len2;
  ft_substring(tmp, line, start, len);
  return (tmp);
}