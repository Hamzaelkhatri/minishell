/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:30:37 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 18:31:23 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_quote1(char *str) {
  int i;

  i = 0;
  while (str[i]) {
    if (str[i] == 34 || str[i] == 39)
      return (1);
    i++;
  }
  return (0);
}

int escape_from_until(char *str, int start, char c) {
  int j;
  char *s;
  int i;

  i = start + 1;
  s = ft_strdup(str);
  j = 0;
  while (s[i]) {
    if (s[i] == c) {
      j = i;
      break;
    }
    i++;
  }
  if (j == 0) {
    printf("Syntax Error: one Quote");
    exit(1);
  }
  return (j);
}

int check_befor(char *str, int i, int o, char quote) {
  if (i == 0) {
    if (str[i] == quote)
      return (1);
  }
  while (i > o) {
    if (str[i] == quote)
      return (1);
    i--;
  }
  return (0);
}

int check_after(char *str) {
  while (*str) {
    if (*str == 34)
      return (1);
    str++;
  }
  return (0);
}