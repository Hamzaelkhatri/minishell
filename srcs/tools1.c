/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:30:37 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 12:54:09 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int escape_from_until(char *str, int start, char c) {
 int j;
  char *s;
  int i;

  i = start +1 ;
  s = strdup(str);
  j = 0;
  while (s[i]) {
    if (s[i] == c) {
      j = i;
      break;
    }
    i++;
  }
  if (j == 0) {
    printf("Syntax Error: One quote_ ");
    exit(1);
  }
  return (j);
}


int check_befor(char *str, int i, int o) {
  if (i == 0) {
    if ( str[i] == '\'' || str[i] == '\"')
      return (1);
  }
  while (i > o) {
    if (str[i] == '\'' || str[i] == '\"')
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
int  witch_quote1(char *s, t_shell *sh) {
  int i;
  char *str;

  i = 0;
  str = strdup(s);
  while (str[i]) {
    if (str[i] == 34) {
      free(str);
      return(1);
    } else if (str[i] == 39) {
           free(str);
      return(1);
    }
    i++;
  }
  return(0);
  // free(s);
}

int escape_from_until1(char *str, int start, char c) {
  int j;
  char *s;
  int i;

  i = start +1 ;
  s = strdup(str);
  j = 0;
  while (s[i]) {
    if (s[i] == c) {
      j = i;
      break;
    }
    i++;
  }
  if (j == 0) {
    printf("Syntax Error: One quote_2");
    exit(1);
  }
  return (j);
}
int escape_from_until2(char *str,   int i, char c) {
  int j;
  char *s;

  s = strdup(str);
  j = 0;
while (s[i] != c) {
  i++;
}
if (s[i] == c) 
      j = i;
  if (j == 0) {
    printf("Syntax Error: One quote_1 ");
    exit(1);
  }
  return (j);
}