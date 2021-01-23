/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:57:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 16:57:07 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void witch_quote(char *s, t_shell *sh) {
  int i;
  char *str;

  i = 0;
  str = ft_strdup(s);
  sh->db_quote = 0;
  sh->sp_quote = 0;
  while (str[i]) {
    if (str[i] == 34) {
      sh->db_quote = 1;
      break;
    } else if (str[i] == 39) {
      sh->sp_quote = 1;
      break;
    }
    i++;
  }
}

char quote_char(char *str, t_shell *sh) {
  char c;
  int i;

  i = 0;
  sh->db_quote = 0;
  sh->sp_quote = 0;
  while (str[i]) {
    if (str[i] == 34) {
      sh->db_quote = 1;
      return ('\"');
    } else if (str[i] == 39) {
      sh->sp_quote = 1;
      return ('\'');
    }
    i++;
  }
  return (0);
}

void ft_check_comma(char *line, t_shell *sh) {
  int i;

  i = 0;
  sh->comma = 0;
  int index = 0;

  while (line[i]) {
if (line[i] == '\'' || line[i] == '\"') {
  if (line[i] == '\"') {
      i = escape_from_until1(line, i +1, '\"') ;
     }
    else if ( line[i] == '\'')
        i = escape_from_until1(line, i +1, '\'');
      }
      if (line[i] == ';') {
        sh->comma = 1;
        break;
    } 
    if(line[i])
    i++;
  }
}
void ft_check_pipe(char *line, t_shell *sh) {
  int i;

  i = 0;
  sh->pipe = 0;
  while (line[i]) {
    if (line[i] == '\'' || line[i] == '\"') {
      if (line[i] == '\"')
        i = escape_from_until1(line, i + 1, '\"');
      else if ( line[i] == '\'')
          i = escape_from_until1(line, i+1, '\'') ;
      if (line[i] == '|') {
        sh->pipe = 1;
        break;
      }
    } else {
      if (line[i] == '|') {
        sh->pipe = 1;
        break;
      }
    }

    i++;
  }
}

int check_one(char *line, t_shell *sh) {
  sh->pipe = 0;
  sh->comma = 0;

  ft_check_comma(line, sh);
  ft_check_pipe(line, sh);
  if (sh->pipe == 1 && sh->comma == 0)
    return (1);
  else if (sh->pipe == 0 && sh->comma == 1)
    return (2);
  else if (sh->pipe == 1 && sh->comma == 1)
    return (3);
  else
    return (0);
}
