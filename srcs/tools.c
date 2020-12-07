#include "minishell.h"

char		*ft_str_in_str(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

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

int				ft_2strlen(char **str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}
