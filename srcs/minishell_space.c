/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:27:51 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 12:44:47 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void *leak(char **spl, int j) {
  j = j - 1;
  while (spl[j]) {
    free(spl[j]);
    j--;
  }
  free(spl);
  return (NULL);
}

static int wordsp(char *str) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i]) {
    while ((str[i] == ' ' || str[i] == '\t') && str[i])
      i++;
    if (str[i] && str[i] != ' ' && str[i] != '\t') {
      i++;
      j++;
    }
    while (str[i] && str[i] != ' ' && str[i] != '\t')
      i++;
  }
  return (j);
}
static int wordsp1(char *str, char quote) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i]) {
    while ((str[i] == ' ' || str[i] == '\t') && str[i] && str[i] != quote)
      i++;
    if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != quote) {
      i++;
      j++;
    } else if (str[i] && str[i] == quote) {
      i = escape_from_until(str, i, quote);
      i++;
      if (str[i] && str[i] != ' ' && str[i] != '\t') {
        i++;
        j++;
      }
      // else
      //   {
      // i++;
      j++;
      //   }
    }
    while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != quote)
      i++;
  }
  return (j);
}

static int carcts_sp1(char *str, char quote) {
  int i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t') {
    if (str[i] == quote)
      i = escape_from_until(str, i, quote);
    i++;
  }
  return (i);
}

static char *alloc_sp1(char **tab, char *src, char quote) {
  int i;
  int j;
  int o;

  j = 0;
  o = 0;
  int k = 0;
  while ((src[o] == ' ' || src[o] == '\t') && src[o] != quote)
    o++;
  while (j < wordsp1(src, quote)) {
    i = 0;
    if (!(tab[j] = malloc(sizeof(char) * (carcts_sp1(&src[o], quote) + 1))))
      return (leak(tab, j));
    while ((src[o] != '\t' && src[o] != ' ' && src[o] != quote) && src[o])
      tab[j][i++] = src[o++];
    if (src[o] == quote) {
      k = escape_from_until(src, o, quote) + 1;
      while (o < k)
        tab[j][i++] = src[o++];
      o = k;
    }
    tab[j][i] = '\0';
    while ((src[o] == '\t' || src[o] == ' ') && src[o])
      o++;
    j++;
  }
  tab[j] = NULL;
  return (*tab);
}

static int carcts_sp(char *str) {
  int i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t') {
    i++;
  }
  return (i);
}

static char *alloc_sp(char **tab, char *src) {
  int i;
  int j;
  int o;

  j = 0;
  o = 0;

  while (src[o] == ' ' || src[o] == '\t')
    o++;
  while (j < wordsp(src)) {
    i = 0;
    if (!(tab[j] = malloc(sizeof(char) * (carcts_sp(&src[o]) + 1))))
      return (leak(tab, j));
    while ((src[o] != '\t' && src[o] != ' ') && src[o]) {
      tab[j][i++] = src[o++];
    }
    tab[j][i] = '\0';
    while ((src[o] == '\t' || src[o] == ' ') && src[o])
      o++;
    j++;
  }
  tab[j] = NULL;
  return (*tab);
}

char **shell_space_split(char const *s, t_shell *sh) {
  int i;
  int j;
  int o;
  char **tab;
  char *str;

  o = 0;
  i = 0;
  j = 0;
  if (!s)
    return (NULL);
  str = (char *)s;

  witch_quote(str, sh);
  // printf("|%d|", sh->sp_quote);
  // printf("|%d|", sh->db_quote);

  if (sh->sp_quote == 1 || sh->db_quote == 1) {
    // puts("here");
    // printf("==>%d\n",wordsp1(str, quote_char(str, sh)));
    tab = malloc(sizeof(char *) * (wordsp1(str, quote_char(str, sh)) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc_sp1(tab, str, quote_char(str, sh));
  } else {
    tab = malloc(sizeof(char *) * (wordsp(str) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc_sp(tab, str);
  }
  // while (tab[j]) {
  //   puts(tab[j]);
  //   j++;
  // }

  return (tab);
}