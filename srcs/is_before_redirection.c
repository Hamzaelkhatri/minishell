/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_before_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:38:53 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/22 12:56:30 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int index_redi(char *line, char c) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (line[i]) {
    if (line[i] == c && (line[i + 1] == '<' || line[i + 1] == '>' ||
                         (line[i + 1] == '>' && line[i + 2] == '>'))) {
      j = i;
      break;
    } else if (line[i] == '<' || line[i] == '>' ||
               (line[i] == '>' && line[i + 1] == '>')) {
      j = i;
      break;
    }
    i++;
  }
  return (j);
}

char *is_befor_redirection(char *line, t_shell *sh) {
  char *tmp;
  char *cmd;
  int i;
  int j;

  i = 0;
  j = 0;
  char c;
  int len;

  len = 0;
  cmd = ft_strdup(line);
  c = quote_char(cmd, sh);
  if (sh->db_quote == 1)
    len = index_redi(cmd, '\"') + 1;
  else if (sh->sp_quote == 1)
    len = index_redi(cmd, '\'') + 1;
  else
    len = ft_strlen(line);
  tmp = malloc(sizeof(char) * (len));
  while (line != NULL) {
    if (line[i] == c && (line[i + 1] == '<' || line[i + 1] == '>' ||
                         (line[i + 1] == '>' && line[i + 2] == '>')))
      break;
    if (line[i] == '<' || line[i] == '>' ||
        (line[i] == '>' && line[i + 1] == '>'))
      break;
    else {
      tmp[j] = line[i];
      i++;
      j++;
    }
  }
  tmp[j] = '\0';
  tmp = ft_strtrim(tmp, " ");
  if (ft_strlen(tmp) == 0)
    tmp = NULL;
  return (tmp);
}

char *is_befor_redirection1(char *line) {
  int i;
  int j;
  char *tmp;
  i = 0;
  j = 0;
  tmp = malloc(sizeof(char) * ft_strlen(line));
  while (line != NULL) {
    tmp[j] = line[i];
    if (line[i] == '>' && line[i + 1] == '>')
      break;
    i++;
    j++;
  }
  tmp[j] = '\0';
  return (tmp);
}
char *befor_direction(char *line, t_shell *sh) {
  char *befor;

  befor = ft_strdup("/0");
  if (check_redirection(line) == 1)
    befor = is_befor_redirection(line, sh);
  else if (check_redirection(line) == 2)
    befor = is_befor_redirection(line, sh);
  else if (check_redirection(line) == 3)
    befor = is_befor_redirection1(line);
  else
    befor = line;
  return (befor);
}


char **redir(char *line) {
  char **tmp;
  tmp = NULL;
  if (space_or_no(line) == 1)
    return (tmp);
  else
    return (search_4_red(line));
}
