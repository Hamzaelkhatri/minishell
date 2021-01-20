/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:59:48 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 18:15:40 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int check_revers_check(char caract, char next_char, char one, char two) {
  if ((caract == one && next_char == two) ||
      (caract == two && next_char == one))
    return (1);
  else
    return (0);
}

int count_array(char **tmp) {
  int i;

  i = 0;
  while (tmp[i] != NULL)
    i++;
  return (i);
}

int check_redirection(char *line) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (line[i] != '\0') {
    if (line[i] == '>' )
      j = 1;
    else if (line[i] == '<')
      j = 2;
    else if (line[i] == '>' && line[i + 1] == '>')
      j = 3;
    i++;
  }
  return (j);
}

int count_redirection(char *line, char redirect) {
  int i = 0;
  int count = 0;

  while (line[i] != '\0') {
    if (line[i] == redirect)
      count++;
    i++;
  }
  return (i);
}