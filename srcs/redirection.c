/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:27:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/06 16:15:56 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_redirection(char *line) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (line[i] != '\0') {
    if (line[i] == '>')
      j = 1;
    else if (line[i] == '<')
      j = 2;
    else if (line[i] == '>' && line[i + 1] == '>')
      j = 3;
    i++;
  }
  return (j);
}

int count_redirection(char *line, char redirect) {
  int i = 0;
  int count = 0;

  while (line[i] != '\0') {
    if (line[i] == redirect)
      count++;
    i++;
  }
  return (i);
}

char *is_befor_redirection(char *line) {
  char *tmp;
  char *cmd;
  int i;
  int j;

  i = 0;
  j = 0;
  // printf("\n\n\n\n\n\n\n\n");
  tmp = malloc(sizeof(char) * (strlen(line)));
  while (line != NULL) {
    tmp[j] = line[i];
    if (line[i] == '<' || line[i] == '>' ||
        (line[i] == '>' && line[i + 1] == '>'))
      break;
    else {
      i++;
      j++;
    }
  }
  tmp[j] = '\0';
  tmp = ft_strtrim(tmp, " ");
  // puts("here1");
  if (ft_strlen(tmp) == 0)
    tmp = NULL;
  return (tmp);
}
char *is_in_redirection(char *line, char redirect) {
  int i;
  int j;
  char *tmp;
  int index = 0;
  int len;
  len = strlen(line);
  i = 0;
  j = 0;
  char *tmp1;
  tmp1 = strdup(line);

  while (line[i] != '\0') {
    if (line[i] == redirect) {
      index = i;
      break;
    }
    i++;
  }
  i = len - index;
  tmp = malloc(sizeof(char) * (i + 1));
  while (i > 0) {
    tmp[j++] = tmp1[index++];
    i--;
  }
  tmp[j] = '\0';
  return (tmp);
}
char *is_in_redirection1(char *line) {
  int i;
  int j;
  char *tmp;
  int index = 0;
  int len;
  len = ft_strlen(line);
  i = 0;
  j = 0;
  char *tmp1;
  tmp1 = ft_strdup(line);

  while (line[i] != '\0') {
    if (line[i] == '>' && line[i + 1] == '>') {
      index = i;
      break;
    }
    i++;
  }
  i = len - index;
  tmp = malloc(sizeof(char) * (i + 1));
  while (i > 0) {
    tmp[j++] = tmp1[index++];
    i--;
  }
  tmp[j] = '\0';
  return (tmp);
}

int search(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if ((str[i] == '>' || str[i] == '<' ||
         (str[i] == '>' && str[i + 1] == '>')) &&
        str[i + 1] != '\0')
      return (1);
    i++;
  }
  return (0);
}

char **search_4_red(char *line) {
  int i;
  int j;
  char **tmp;
  char **str;

  i = 0;
  j = 0;
  str = malloc(sizeof(char) * 100);
  tmp = ft_space_split(line);
  while (tmp[i] != NULL) {
    if (search(tmp[i]) == 1)
      str[j++] = ft_strdup(tmp[i]);
    i++;
  }
  return (str);
}

int search_4_redirect(char *line) {
  int i;

  i = 0;
  while (line[i]) {
    if (line[i] == '>' || line[i] == '<' ||
        (line[i] == '>' && line[i + 1] == '>'))
      return (1);
    i++;
  }
  return (0);
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
char *befor_direction(char *line) {
  char *befor;

  befor = ft_strdup("/0");
  if (check_redirection(line) == 1)
    befor = is_befor_redirection(line);
  else if (check_redirection(line) == 2)
    befor = is_befor_redirection(line);
  else if (check_redirection(line) == 3)
    befor = is_befor_redirection1(line);
  else
    befor = line;
  return (befor);
}

char *in_direction(char *line) {
  char *befor;
  if (check_redirection(line) == 1)
    befor = is_in_redirection(line, '>');
  else if (check_redirection(line) == 2)
    befor = is_in_redirection(line, '<');
  else if (check_redirection(line) == 3)
    befor = is_in_redirection1(line);
  else
    befor = NULL;
  return (befor);
}

int space_or_no(char *line) {
  int i = 0;

  while (line[i] != '\0') {
    if ((line[i] == '>' || line[i] == '<' ||
         (line[i] == '>' && line[i + 1] == '>')) &&
        line[i + 1] == '\0')
      return (1);
    i++;
  }
  return (0);
}

// char **is_after_redirection(char *line) {
//   int i = 0;
//   int j = 0;
//   int index = 0;
//   char **tmp;
//   char **tmp1;
//   char **str;
//   char **result;
//   tmp1 = ft_space_split(line);
//   tmp = malloc(sizeof(char) * strlen(line));
//   i = 0;
//   while (tmp1[i] != NULL) {
//     if ((ft_strcmp(tmp1[i], ">") == 0))
//       tmp[j++] = ft_strjoin(tmp1[i], tmp1[i + 1]);
//     else if ((ft_strcmp(tmp1[i], ">>") == 0))
//       tmp[j++] = ft_strjoin(tmp1[i], tmp1[i + 1]);
//     else if ((ft_strcmp(tmp1[i], "<") == 0))
//       tmp[j++] = ft_strjoin(tmp1[i], tmp1[i + 1]);
//     else {
//       if (search(tmp1[i]) == 1)
//         tmp[j++] = ft_strdup(tmp1[i]);
//     }
//     i++;
//   }
//   return (tmp);
// }

char **redir(char *line) {
  char **tmp;
  tmp = NULL;
  if (space_or_no(line) == 1)
    return (tmp);
  //  return (is_after_redirection(line));
  else
    return (search_4_red(line));
}

// char **searc_4_it(char *line) {
//   int i = 0;

//   // while (line[i] != '\0') {
//   // }
// }