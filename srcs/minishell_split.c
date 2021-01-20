/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 00:03:18 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/01/20 11:01:41 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  witch_quote1(char *s, t_shell *sh) {
  int i;
  char *str;

  i = 0;
  str = ft_strdup(s);
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

int words1(char *str, char c, char quote) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i]) {
    while (str[i] == c && str[i])
      i++;
    while (str[i] != c && str[i] != quote && str[i])
      i++;
    if (str[i] != c && str[i] != quote && str[i]) {
      i++;
      j++;
    } else if (str[i] == quote && str[i]) {
      i = escape_from_until(str, i, quote) + 1;
      if (str[i] == c)
        i++;
      else {
        while (str[i] != c && str[i])
          i++;
        if (str[i] == c)
          i++;
      }
      i++;
    }
    j++;
  }
  return (j);
}

static int words(char *str, char c) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i]) {
    while (str[i] == c && str[i])
      i++;
    if (str[i] && str[i] != c) {
      i++;
      j++;
    }
    while (str[i] && str[i] != c)
      i++;
  }
  return (j);
}

static void *leak(char **spl, int j) {
  j = j - 1;
  while (spl[j]) {
    free(spl[j]);
    j--;
  }
  free(spl);
  return (NULL);
}

static int carcts(char *str, char c) {
  int i;

  i = 0;
  while (str[i] && str[i] != c) {
    i++;
  }
  return (i);
}

static int carcts1(char *line, char c, int o, char quote) {
  int i;
  int j;

  i = o;
  j = 0;
  while (line[i] != '\0') {
    if (line[i] == quote) {
      i = escape_from_until(line, i, quote) + 1;
      if (line[i] == c) {
        j = i;
        break;
      }
    } else if (line[i] == c) {
      j = i;
      break;
    }
    i++;
    j++;
  }
  return (j);
}

static char *alloc1(char **tab, char *src, char c, char quote) {
  int i;
  int j;
  int o;
  int k;

  j = 0;
  o = 0;
  i = 0;
  while (src[o] == c)
    o++;
  while (j < words1(src, c, quote)) {
    i = 0;
    k = carcts1(src, c, o, quote);
    if (!(tab[j] = malloc(sizeof(char) *
                          (carcts1(src, c, o, quote) +
                           1)))) // carcts1(&src[o], c,o) + 1 tfakri!!!
      return (leak(tab, j));
    if (check_befor(src, k, o, quote) == 1) {
      while (o < k && src[o]) {
        tab[j][i] = src[o];
        o++;
        i++;
      }
    } else {
      while ((src[o] != c && src[o])) {
        tab[j][i] = src[o];
        o++;
        i++;
      }
      // puts(&src[o]);
    }
    tab[j][i] = '\0';

    while (src[o] == c && src[o])
      ++o;
    j++;
  }
  tab[j] = NULL;
  return (*tab);
}

static char *alloc(char **tab, char *src, char c) {
  int i;
  int j;
  int o;

  j = 0;
  o = 0;
  while (src[o] == c)
    o++;
  while (j < words(src, c)) {
    i = 0;
    if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o], c) + 1))))
      return (leak(tab, j));
    while (src[o] != c && src[o])
      tab[j][i++] = src[o++];
    tab[j][i] = '\0';
    while (src[o] == c && src[o])
      o++;
    j++;
  }
  tab[j] = NULL;
  return (*tab);
}

char **ft_minishell_split(char const *s, char c, t_shell *sh) {
  int j;
  char **tab;
  char *str;

  j = 0;
  if (!s)
    return (NULL);
  str = (char *)s;
  // witch_quote(str, sh);
  if (  witch_quote1(str, sh)== 1) {
    tab = malloc(sizeof(char *) * (words1(str, c, quote_char(str, sh)) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc1(tab, str, c, quote_char(str, sh));
  } else {
    tab = malloc(sizeof(char *) * (words(str, c) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc(tab, str, c);
  }
  return (tab);
}