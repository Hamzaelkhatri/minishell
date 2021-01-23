/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:27:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 17:44:41 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char *is_in_redirection(char *line, char redirect) {
  int i;
  int j;
  char *tmp;
  int index = 0;
  int len;
  len = strlen(line);
  i = 0;
  j = 0;
  char *tmp1;
  tmp1 = ft_strdup(line);

  while (line[i] != '\0') {
    if (line[i] == redirect) {
      index = i;
      break;
    }
    i++;
  }
  i = len - index;
  tmp = malloc(sizeof(char) * (i + 1));
  while (i > 0) {
    tmp[j++] = tmp1[index++];
    i--;
  }
  tmp[j] = '\0';
  return (tmp);
}
char *is_in_redirection1(char *line) {
  int i;
  int j;
  char *tmp;
  int index = 0;
  int len;
  len = ft_strlen(line);
  i = 0;
  j = 0;
  char *tmp1;
  tmp1 = ft_strdup(line);
  while (line[i] != '\0') {
    if (line[i] == '>' && line[i + 1] == '>') {
      index = i;
      break;
    }
    i++;
  }
  i = len - index;
  tmp = malloc(sizeof(char) * (i + 1));
  while (i > 0) {
    tmp[j++] = tmp1[index++];
    i--;
  }
  tmp[j] = '\0';
  return (tmp);
}



int search_4_redirect(char *line) {
  int i;

  i = 0;
  while (line[i]) {
    if (line[i] == '>' || line[i] == '<' ||
        (line[i] == '>' && line[i + 1] == '>'))
      return (1);
    i++;
  }
  return (0);
}


char *in_direction(char *line) {
  char *befor;
  if (check_redirection(line) == 1)
    befor = is_in_redirection(line, '>');
  else if (check_redirection(line) == 2)
    befor = is_in_redirection(line, '<');
  else if (check_redirection(line) == 3)
    befor = is_in_redirection1(line);
  else
    befor = NULL;
  return (befor);
}

int space_or_no(char *line) {
  int i = 0;

  while (line[i] != '\0') {
    if ((line[i] == '>' || line[i] == '<' ||
         (line[i] == '>' && line[i + 1] == '>')) &&
        line[i + 1] == '\0')
      return (1);
    i++;
  }
  return (0);
}

