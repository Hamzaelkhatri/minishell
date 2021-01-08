#include "minishell.h"

char *ft_str_in_str(const char *s1, const char *s2) {
  size_t i;
  size_t j;

  i = 0;
  j = 0;
  if (!s2[j])
    return ((char *)s1);
  while (s1[i]) {
    j = 0;
    if (s1[i] == s2[j]) {
      j = 1;
      while (s2[j] && s2[j] == s1[i + j])
        j++;
      if (!s2[j] && !s1[i + j])
        return ((char *)&s1[i]);
    }
    i++;
  }
  return (NULL);
}

int ft_2strlen(char **str) {
  int i;

  i = 0;
  while (str[i] != 0)
    i++;
  return (i);
}

int count_line(char **env) {
  int i = 0;
  if (!env)
    return (0);
  while (env[i])
    i++;
  return (i);
}

int search_str(char *str1, char *str2, int l1, int l2) {
  int i;
  i = 0;

  if (l1 != l2 || l1 == 0 || l2 == 0)
    return (0);
  else if (ft_strncmp(str1, str2, l1) == 0)
    return (1);
  return (0);
}

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
  // int i;
  char *result;
  char *tmp1;

  // i = 1;
  result = malloc(sizeof(char) * (ft_strlen(*tmp) + ft_strlen(tmp1) + 1));
  tmp1 = malloc(sizeof(char) * (ft_strlen(*tmp) + ft_strlen(tmp1) + 1));
  while (tmp[i] != NULL) {
    result = ft_str_join(tmp1, " ", tmp[i]);
    tmp1 = strdup(result);
    i++;
  }
  result = ft_strtrim(result, " ");
  return (result);
}

char *concat_1(char *tmp, char *tmp1) {
  int i;
  char *result;

  i = 0;
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
  return (result);
}
