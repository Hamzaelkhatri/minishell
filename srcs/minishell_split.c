/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 00:03:18 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/01/23 12:50:02 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_quote1(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] == 34 || str[i] == 39)
      return (1);
    i++;
  }
  return (0);
}

int check_befor111(char *str, int i, int o)
{
  if (i == 0)
  {
    if (str[i] == '\'' || str[i] == '\"')
      return (1);
  }
  while (i > o)
  {
    if (str[i] == '\'' || str[i] == '\"')
      return (1);
    i--;
  }
  return (0);
}

int escape_from_until3(char *str, int start, char c)
{
  int j;
  char *s;
  int i;

  i = start + 1;
  s = strdup(str);
  j = 0;
  while (s[i] != c)
  {
    i++;
  }
  if (s[i] == c)
    j = i;
  if (j == 0)
  {
    printf("Syntax Error: One quote_3 ");
    exit(1);
  }
  return (j);
}
int escape_from_until4(char *str, int i, char c)
{
  int j;
  char *s;

  s = strdup(str);
  j = 0;
  while (s[i] != c)
  {
    i++;
  }
  if (s[i] == c)
    j = i;
  if (j == 0)
  {
    printf("Syntax Error: One quote_1 ");
    exit(1);
  }
  return (j);
}
int words1(char *str, char c)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i])
  {
    while (str[i] == c && str[i] && (str[i] != '\"' && str[i] != '\''))
      i++;
    if (str[i] != c && (str[i] != '\"' && str[i] != '\'') && str[i])
    {
      while (str[i] != c && (str[i] != '\"' && str[i] != '\'') && str[i])
      {
        i++;
      }
      j++;
    }
    if ((str[i] == '\"' || str[i] == '\'') && str[i])
    {
      if (str[i] == '\"')
      {
        i = escape_from_until4(str, i + 1, '\"') + 1;
      }
      else if (str[i] == '\'')
        i = escape_from_until4(str, i + 1, '\'') + 1;
    }

    while (str[i] != c && str[i] && (str[i] != '\"' && str[i] != '\''))
      i++;
  }
  return (j);
}

static int words(char *str, char c)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i])
  {
    while (str[i] == c && str[i])
      i++;
    if (str[i] && str[i] != c)
    {
      i++;
      j++;
    }
    while (str[i] && str[i] != c)
      i++;
  }
  return (j);
}

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

static int carcts(char *str, char c)
{
  int i;

  i = 0;
  while (str[i] && str[i] != c)
  {
    i++;
  }
  return (i);
}

static int carcts1(char *line, char c, int o)
{
  int i;
  int j;
  i = o;
  j = 0;

  while (line[i])
  {
    if (line[i] == '\"' || line[i] == '\'')
    {
      if (line[i] == '\"')
        i = escape_from_until3(line, i, '\"') + 1;
      else if (line[i] == '\'')
        i = escape_from_until3(line, i, '\'') + 1;
      if (line[i] == c)
      {
        j = i - 1;
        return (j);
        // break;
      }
    }
    if (line[i] == c)
    {
      j = i - 1;
      return (j);
      //   break;
    }
    i++;
    j++;
  }
  return (i);
}

static char *alloc1(char **tab, char *src, char c, char quote)
{
  int i;
  int j;
  int o;
  int k;

  j = 0;
  o = 0;
  i = 0;
  src = ft_strtrim(src, " ");
  while (src[o] == c)
    o++;
  while (j < words1(src, c))
  {
    i = 0;

    k = carcts1(src, c, o);

    if (!(tab[j] = malloc(sizeof(char) * (k + 1))))
      return (leak(tab, j));
    while (o <= k && src[o])
    {
      tab[j][i] = src[o];
      o++;
      i++;
    }
    while ((src[o] == ' ' || src[o] == c || src[o] == '\t') && src[o])
      ++o;
    tab[j][i] = '\0';
    j++;
  }
  tab[j] = NULL;
  return (*tab);
}

static char *alloc(char **tab, char *src, char c)
{
  int i;
  int j;
  int o;

  j = 0;
  o = 0;
  while (src[o] == c)
    o++;
  while (j < words(src, c))
  {
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

int check_quote2(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] == 34 || str[i] == 39)
      return (1);
    i++;
  }
  return (0);
}
char **ft_minishell_split(char const *s, char c, t_shell *sh)
{
  int j;
  char **tab;
  char *str;

  j = 0;
  if (!s)
    return (NULL);
  str = (char *)s;
  if (check_quote2(str) == 1)
  {
    tab = malloc(sizeof(char *) * (words1(str, c)));
    if (!tab)
      return (NULL);
    tab[j] = alloc1(tab, str, c, (words1(str, c)));
  }
  else
  {
    tab = malloc(sizeof(char *) * (words(str, c) + 1));
    if (!tab)
      return (NULL);
    tab[j] = alloc(tab, str, c);
  }
  return (tab);
}