# include "../libft/libft.h"
#include <stdio.h>

size_t		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*source;
	char	*copy;

	i = 0;
	source = (char *)src;
	copy = (char *)dest;
	if (!source && !copy)
		return (NULL);
	if (source == copy)
		return (dest);
	while (i < n)
	{
		copy[i] = source[i];
		i++;
	}
	return (dest);
}

char	*strstart(char *str, char *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && set[j])
	{
		if (str[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (&str[i]);
}

int		strend(char *str, char *set)
{
	int		i;
	int		j;

	i = ft_strlen(str);
	j = 0;
	while (i > 0 && set[j])
	{
		if (str[i - 1] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*tab;
	char		*delt;
	char		*ptr;
	char		*string;
	size_t		i;

	tab = (char *)s1;
	delt = (char *)set;
	if (!s1 || !set)
		return (NULL);
	string = strstart(tab, delt);
	i = strend(string, delt);
	ptr = malloc(sizeof(char) * i + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, string, i);
	ptr[i] = '\0';
	return (ptr);
}

int main()
{
    printf("==>%s",ft_strtrim("          cd .. "," "));

}
