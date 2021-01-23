/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:27:51 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 17:42:23 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void *leak(char **spl, int j)
{
  j = j - 1;
  while (spl[j])
  {
    free(spl[j]);
    j--;
  }
  free(spl);
  return (NULL);
}

char quote_char1(char *s, int i)
{

  char *str;
  str = strdup(s);
  // puts(s);
  while (str[i])
  {
    if (str[i] == 34)
    {
      // sh->db_quote = 1;
      return ('\"');
    }
    else if (str[i] == 39)
    {
      // sh->sp_quote = 1;
      return ('\'');
    }
    i++;
  }
  return ('\0');
}

static int wordsp(char *str)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i])
  {
    while ((str[i] == ' ' || str[i] == '\t') && str[i])
      i++;
    if (str[i] && str[i] != ' ' && str[i] != '\t')
    {
      i++;
      j++;
    }
    while (str[i] && str[i] != ' ' && str[i] != '\t')
      i++;
  }
  return (j);
}
static int wordsp1(char *str)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i])
  {
    while ((str[i] == ' ' || str[i] == '\t') && str[i] && (str[i] != '\"' && str[i] != '\''))
      i++;
    if (str[i] && str[i] != ' ' && str[i] != '\t' && (str[i] != '\"' && str[i] != '\''))
    {
      i++;
      j++;
    }
    if (str[i] == '\"' || str[i] == '\'')
    {      

      if (str[i] == '\"') {

        i = escape_from_until1(str, i + 1, '\"');
      }
      else if (str[i] == '\'')
        i = escape_from_until1(str, i +1, '\'') ;
      i++;

      if (str[i] && str[i] != ' ' && str[i] != '\t')
      {
        i++;
        j++;
      }
      j++;
    }
    while (str[i] && str[i] != ' ' && str[i] != '\t' && (str[i] != '\"' && str[i] != '\''))
      i++;
    // i++;
  }
  return (j);
}

static int carcts_sp1(char *str, char quote)
{
  int i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t')
  { 
    if (str[i] == quote)
    {
      i = escape_from_until1(str, i+1, quote);
    }
    i++;
  }
  return (i);
}
// int escape_from_until2(char *str,   int i, char c) {
//   int j;
//   char *s;

//   s = strdup(str);
//   j = 0;
// while (s[i] != c) {
//   i++;
// }
// if (s[i] == c)
//       j = i;
//   if (j == 0) {
//     printf("Syntax Error: One quote ");
//     exit(1);
//   }
//   return (j);
// }
static char *alloc_sp1(char **tab, char *src, char quote)
{
  int i;
  int j;
  int o;

  j = 0;
  o = 0;
  int k = 0;
  while ((src[o] == ' ' || src[o] == '\t') && src[o] != quote)
    o++;
  while (j < wordsp1(src))
  {
    i = 0;
    quote = quote_char1(src, o);

    if (!(tab[j] = malloc(sizeof(char) * (carcts_sp1(&src[o], quote) + 1))))
      return (leak(tab, j));
    while ((src[o] != '\t' && src[o] != ' ' && src[o] != quote) && src[o])
      tab[j][i++] = src[o++];
    if (src[o] == quote && src[o])
    {
      k = escape_from_until2(src, o + 1, quote) + 1;
      while (o < k && src[o])
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

static int carcts_sp(char *str)
{
  int i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t')
  {
    i++;
  }
  return (i);
}

static char *alloc_sp(char **tab, char *src)
{
  int i;
  int j;
  int o;

  j = 0;
  o = 0;

  while (src[o] == ' ' || src[o] == '\t')
    o++;
  while (j < wordsp(src))
  {
    i = 0;
    if (!(tab[j] = malloc(sizeof(char) * (carcts_sp(&src[o]) + 1))))
      return (leak(tab, j));
    while ((src[o] != '\t' && src[o] != ' ') && src[o])
    {
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

char **shell_space_split(char const *s)
{
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
  if (check_quote1(str) == 1)
  {
    // printf("==>%d", (wordsp1(str)));
    tab = malloc(sizeof(char *) * (wordsp1(str) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc_sp1(tab, str, quote_char1(str, 0));
  }
  else
  {
    tab = malloc(sizeof(char *) * (wordsp(str) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc_sp(tab, str);
  }
  return (tab);
}
