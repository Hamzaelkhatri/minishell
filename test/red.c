/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zainabdnayagmail.com <zainabdnayagmail.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:41:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/05 10:16:37 by zainabdnaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

char *ft_strjoin(char const *s1, char const *s2) {
  char *p;
  size_t i;
  size_t j;
  size_t k;

  i = 0;
  j = 0;
  k = 0;
  if (s1 && s2) {
    p = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
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
int ft_strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;

  i = 0;
  if ((!s1 || !s2) && n == 0)
    return (0);
  while (s1[i] != '\0' && s2[i] != '\0' && i < n) {
    if (s1[i] != s2[i])
      return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
  }
  if (i < n &&
      ((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
  return (0);
}

// char *is_befor_redirection(char *line, char redirect) {
//   int i;
//   int j;
//   char *tmp;
//   i = 0;
//   j = 0;
//   tmp = ft_strdup("\0");
//   while (line != NULL) {
//     tmp[j] = line[i];
//     if (line[i] == redirect)
//       break;
//     i++;
//     j++;
//   }
//   tmp[j] = '\0';
//   return (tmp);
// }
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
  while (i > 0 && tmp1 != NULL) {
    tmp[j++] = tmp1[index++];
    i--;
  }
  tmp[j] = '\0';
  return (tmp);
}

int ft_strcmp(const char *s1, const char *s2) {
  int i;

  i = 0;
  while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
    i++;
  return (s1[i] - s2[i]);
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

char **is_after_redirection(char *line) {
  int i = 0;
  int j = 0;
  int index = 0;
  char **tmp;
  char **tmp1;
  char **str;
  char **result;
  tmp1 = ft_space_split(line);
  tmp = malloc(sizeof(char) * strlen(line));
  i = 0;
  while (tmp1[i] != NULL) {
    if ((ft_strcmp(tmp1[i], ">") == 0))
      tmp[j++] = ft_strjoin(tmp1[i], tmp1[i + 1]);
    else if ((ft_strcmp(tmp1[i], ">>") == 0))
      tmp[j++] = ft_strjoin(tmp1[i], tmp1[i + 1]);
    else if ((ft_strcmp(tmp1[i], "<") == 0))
      tmp[j++] = ft_strjoin(tmp1[i], tmp1[i + 1]);
    else {
      if (search(tmp[i]) == 1)
        tmp[j++] = ft_strdup(tmp[i]);
    }
    i++;
  }
  return (tmp);
}
int space_or_no(char *line) {
  if (ft_strcmp(line, ">") == 0 || ft_strcmp(line, ">") == 0 ||
      ft_strcmp(line, ">>") == 0)
    return (1);
  else
    return (0);
}

char *is_befor_redirection(char *line) {
  char *tmp;
  char *cmd;
  int i;
  int j;

  i = 0;
  j = 0;
  tmp = ft_strdup("\0");
  while (line != NULL) {
    tmp[j] = line[i];
    if (line[i] == '<' || line[i] == '>' ||
        (line[i] == '>' && line[i + 1] == '>'))
      break;
    i++;
    j++;
  }
  tmp[j] = '\0';
  return (tmp);
}
int main() {
  int i;

  printf("==>|%s|\n",is_befor_redirection("echo hello samir hamza hiba >file3"));
}