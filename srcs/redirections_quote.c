/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:03:28 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 12:40:53 by zdnaya           ###   ########.fr       */
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

char *no_quote(char *str)
{
  int i;
  char *c;
  char *result;

  result = NULL;
  if (str == NULL)
    return (NULL);
  if (we_have_quote(str) == 1)
  {
    c = malloc(sizeof(char) * 2);
    i = 10;
    while (str[i])
    {
      if (str[i] ==  '\"')
      {
        c[0] = '\"';
        break;
      }
      else if (str[i] == '\'')
      {
        c[0] = '\'';
        break;
      }
      i++;
    }
    c[1] = '\0';
    result = ft_strtrim(str, c);
    result = ft_strtrim(result, " ");
    // puts(result);
  }
  else
  {
    result = ft_strtrim(str, " ");
  }
  // free(str);
  return (result);
}