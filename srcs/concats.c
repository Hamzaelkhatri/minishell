/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:30:44 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 12:20:24 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strcmp(const char *s1, const char *s2) {
  size_t i;

  i = 0;
  if ((!s1 || !s2))
    return (-1);
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i])
      return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
  }
  if (((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
  return (0);
}

char *ft_str_join(char *s1, char *s2, char *s3) {
  char *result;
  char *tmp;

  tmp = ft_strjoin(s1, s2);
  result = ft_strjoin(tmp, s3);
  return (result);
}

char *concat(char **tmp, int i) {
  char *result;

  result = NULL;
  if (tmp[i] == NULL) {
    return (NULL);
  }
  while (tmp[i] != NULL) {
    result = concat_space(no_quote(tmp[i]), result);
    i++;
  }
  result = ft_strtrim(result, " ");
  return (no_quote(result));
}

char *concat_space(char *tmp, char *tmp1) {
  int i;
  char *result;

  i = 0;
  if (tmp1 == NULL && tmp == NULL)
    return (NULL);
  if (tmp1 == NULL && tmp != NULL) {
    result = malloc(sizeof(char) * (ft_strlen(tmp)) + 1);
    result = ft_strdup(tmp);
    result = ft_strtrim(result, " ");
  } else if (tmp1 != NULL && tmp == NULL) {
    result = malloc(sizeof(char) * (ft_strlen(tmp1)) + 1);
    result = ft_strdup(tmp1);
    result = ft_strtrim(result, " ");
  } else {
    result = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(tmp1) + 1));
    result = ft_str_join(tmp1, " ", tmp);
    tmp1 = strdup(result);
    result = ft_strtrim(result, " ");
  }
  return (no_quote(result));
}

