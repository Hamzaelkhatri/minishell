/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_after_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:37:11 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 17:37:28 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *is_after_redirection(char *line, t_shell *sh, char *one_part) {
  char *tmp;
  int index;
  int len;
  int len1;
  int len2;
  int start;
  int i;

  i = 0;
  if (one_part == NULL)
    len2 = 0;
  else
    len2 = ft_strlen(one_part);
  len = ft_strlen(line);
  tmp = malloc(sizeof(char) * ((len - len2) + 1));
  ft_substring(tmp, line, len2, len - len2);
  while (tmp[i] != '\0') {
    if (((tmp[i] == '>' || tmp[i] == '<' ||
          (tmp[i] == '>' && tmp[i + 1] == '>')) &&
         tmp[i + 1] == '\0')) {
      printf("Syntax Error : Enter a proper file name.");
      exit(1);
    }
    i++;
  }
  return (tmp);
}

int remenber_index(char *line, char c, int i) {
  int index;

  index = 0;
  while (line[i] != '\0') {
    if (line[i] == c && (line[i + 1] == '<' || line[i + 1] == '>' ||
                         (line[i + 1] == '>' && line[i + 2] == '>'))) {
      index = i;
      break;
    } else if (line[i] == '<' || line[i] == '>' ||
               (line[i] == '>' && line[i + 1] == '>')) {
      index = i;
      break;
    } else
      i++;
  }
  return (index);
}

int remenber_index1(char *line) {
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

