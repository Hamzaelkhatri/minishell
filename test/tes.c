/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:17:54 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/06 16:25:43 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>

#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>

void *ft_memcpy(void *dest, const void *src, size_t n) {
  size_t i;
  char *source;
  char *copy;

  i = 0;
  source = (char *)src;
  copy = (char *)dest;
  if (!source && !copy)
    return (NULL);
  if (source == copy)
    return (dest);
  while (i < n) {
    copy[i] = source[i];
    i++;
  }
  return (dest);
}

static int words(char *str) {
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

static void *leak(char **spl, int j) {
  j = j - 1;
  while (spl[j]) {
    free(spl[j]);
    j--;
  }
  free(spl);
  return (NULL);
}

static int carcts(char *str) {
  int i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t') {
    i++;
  }
  return (i);
}

static char *alloc(char **tab, char *src) {
  int i;
  int j;
  int o;

  j = 0;
  o = 0;
  while (src[o] == ' ' || src[o] == '\t')
    o++;
  while (j < words(src)) {
    i = 0;
    if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o]) + 1))))
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

char **ft_space_split(char const *s) {
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
  tab = malloc(sizeof(char *) * (words(str) + 1));
  if (!tab)
    return (NULL);
  tab[j] = alloc(tab, str);
  return (tab);
}

char *strstart(char *str, char *set) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i] && set[j]) {
    if (str[i] == set[j]) {
      i++;
      j = 0;
    } else
      j++;
  }
  return (&str[i]);
}

int strend(char *str, char *set) {
  int i;
  int j;

  i = strlen(str);
  j = 0;
  while (i > 0 && set[j]) {
    if (str[i - 1] == set[j]) {
      i--;
      j = 0;
    } else
      j++;
  }
  return (i);
}

char *ft_strtrim(char const *s1, char const *set) {
  char *tab;
  char *delt;
  char *ptr;
  char *string;
  size_t i;

  tab = (char *)s1;
  delt = (char *)set;
  if (!s1 || !set)
    return (NULL);
  string = strstart(tab, delt);
  i = strend(string, delt);
  ptr = malloc(sizeof(char) * i + 1);
  if (!ptr)
    return (NULL);
  memcpy(ptr, string, i);
  ptr[i] = '\0';
  return (ptr);
}

char *ft_strdup(const char *s1) {
  int i;
  char *ptr;

  i = 0;
  while (s1[i])
    i++;
  ptr = malloc(sizeof(char) * i + 1);
  if (ptr == NULL)
    return (NULL);
  i = 0;
  while (s1[i]) {
    ptr[i] = s1[i];
    i++;
  }
  ptr[i] = '\0';
  return (ptr);
}

int remenber_index(char *line) {
  int i;
  int index;

  i = 0;
  index = 0;
  while (line[i] != '\0') {
    if (line[i] == '<' || line[i] == '>' ||
        (line[i] == '>' && line[i + 1] == '>')) {
      index = i;
      break;
    } else
      i++;
  }
  return (index);
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

char *ft_substring(char *destination, const char *source, int start, int len) {

  while (len > 0) {
    *destination = *(source + start);
    destination++;
    source++;
    len--;
  }
  *destination = '\0';
  return destination;
}

// char *is_after_redirection(char *line) {
//   char *tmp;
//   int index;
//   int len;
//   int len1;
//   int len2;
//   int start;
//   char *one_part;

//   tmp = ft_strdup("\0");
//   one_part = ft_strdup("\0");
//   one_part = is_befor_redirection(line);
//   len2 = strlen(one_part);
//   len1 = strlen(line);
//   start = remenber_index(line);
//   len = len1 - len2;
//   ft_substring(tmp, line, start, len);
//   return (tmp);
// }

char *is_after_redirection(char *line) {
  char *tmp;
  int index;
  int len;
  int len1;
  int len2;
  int start;
  char *one_part;

  len1 = ft_strlen(line);
  one_part = malloc(sizeof(char) * (len1 + 1));
  tmp = malloc(sizeof(char) * (len1 + 1));
  one_part = is_befor_redirection(line);
  if (one_part == NULL)
    len2 = 0;
  else
    len2 = strlen(one_part);
  start = remenber_index(line);
  len = len1 - len2;
  ft_substring(tmp, line, start, len);
  return (tmp);
}

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
    // else
    //   j= 0;
    i++;
  }
  return (j);
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

void sort_after_redirectio(char *line) {
  char **tmp;
  int i;
  char *redirect;
  char *sign_redirect;
  char *file_name;
  char *arg;
  i = 0;
  tmp = ft_space_split(line);
  while (tmp[i] != NULL) {
    if (check_redirection(tmp[i]) != 0 &&
        (strcmp(tmp[i], ">>") == 0 || strcmp(tmp[i], ">") == 0 ||
         strcmp(tmp[i], "<") == 0)) {
      sign_redirect = ft_strdup(tmp[i]);
      file_name = tmp[i + 1];
      // printf("==>|%s|\n", file_name);
      i = i + 2;
    } else if (check_redirection(tmp[i]) != 0) {
      redirect = ft_strdup(tmp[i]);
      i++;
    } else {
      arg = ft_strdup(tmp[i]);
      i++;
    }
  }
}
size_t ft_strlen(const char *str) {
  int i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}
char *ft_strjoin(char const *s1, char const *s2) {
  char *p;
  size_t i;
  size_t j;
  size_t k;

  i = 0;
  j = 0;
  k = 0;
  if (s1 && s2) {
    p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (p == NULL)
      return (NULL);
    while (s1[j]) {
      p[i++] = s1[j++];
    }
    while (s2[k]) {
      p[i++] = s2[k++];
    }
    p[i] = '\0';
    return (p);
  }
  return (NULL);
}

char *seperat_file_name(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * (strlen(tmp)))))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<')
      i++;
    else if ((tmp[i] == '>' && tmp[i + 1] == '>'))
      i = i + 2;
    else {
      res[j] = tmp[i];
      j++;
      i++;
    }
  }
  res[j] = '\0';
  return (res);
}

char *seperat_red(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * 2)))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<') {
      res[0] = tmp[i];
      res[1] = '\0';
      break;
    } else if ((tmp[i] == '>' && tmp[i + 1] == '>')) {
      res = ft_strdup(">>");
      // *res = '\0';
      // i++;
      break;
    } else {
      i++;
    }
  }
  return (res);
}

int main() {

  // printf("|%s|\n",
  //
  // char *after = is_after_redirection(
  //     "echo hello samir  <file2 hamza >> file3 hello world <file4 > file5");
  // puts(after);
  // printf("|%s|\n",is_befor_redirection("echo hello samir  <file2 hamza >>
  // file3"));
  // sort_after_redirectio(after);
  char *str;

  printf("==>|%s|\n", is_after_redirection("<file >>file"));
  return 0;
}

// int main() {
//   char *dest;
//   char *src = "hello";
//   // printf("befor : |%s|",
//   //        is_after_redirection("echo hello samir  <file2 hamza <<
//   file3")); printf("==>%zu\n", ft_strlcpy(dest, src, 3));
//   // printf("{%s}\n", dest);
//   return (0);
// }