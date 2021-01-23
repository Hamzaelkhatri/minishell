/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:03:28 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 15:38:58 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int quote_bfr_red(char *s)
{
  int i;

  if ((s[i] == '>' || s[i] == '<' || (s[i] == '>' && s[i + 1] == '>')) &&
      (s[i + 1] != '\0' || s[i + 1] != '\n'))
  {
    while (s)
    {
      if ((s[i] == '\'' || s[i] == '\"') &&
          (s[i + 1] == '<' || s[i + 1] == '>' ||
           (s[i + 1] == '>' && s[i + 2] == '>')))
      {
        return (1);
        // puts("here");
      }
      i++;
    }
  }
  return (0);
}

int we_have_quote(char *str)
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

int exist_equal(char *str) {


  int i;
  i = 0;

  while (str[i]) {
    if (str[i] == '=')
      return (1);
    i++;
    }
  return(0);
}

char *no_quote(char *s)
{
  int i;
  char *c;
  char *result;
  int j;
  char *str;
  char quote;

  quote = 0;
  if (s == NULL)
    return (NULL);

  str = ft_strdup(s);
  result = malloc(sizeof(char) * strlen(str));
  // puts(str);
  if (we_have_quote(str) == 1 && exist_equal(str) == 0) {
    quote = 0;
      j = 0;
  i = 0;
    while (str[i])
    {
      if ((str[i] == '\"' || str[i] == '\'') &&
          (quote == str[i] || quote == 0)) {
        quote = str[i];
        i++;
          }
      else {
        result[j] = str[i];
        j++;
        i++;
      }
    }
    result[j] = '\0';
  }
   else
    result = ft_strdup(str);
  result = ft_strtrim(result,"\n");
  return (result);
}