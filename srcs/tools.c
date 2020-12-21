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

int count_line(char **env)
{
	int i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

int		search_str(char *str1, char *str2, int l1, int l2)
{
	int i;
	i = 0;

	if (l1 != l2 || l1 == 0 || l2 == 0)
		return (0);
	else if (ft_strncmp(str1,str2,l1) == 0)
		return (1);
	return (0);
}