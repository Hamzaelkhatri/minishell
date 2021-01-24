#include "minishell.h"

char	*ft_str_in_str(const char *s1, const char *s2)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
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

int		count_line(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

int ft_strcmp(const char *s1, const char *s2) 
{
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

