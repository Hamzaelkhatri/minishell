
#include "minishell.h"

static int words(char *str)
{
	int index = 0;
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		// ft_putendl_fd(str,1);
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		if (str[i] && str[i] != ' ' && str[i] != '\t')
			j++;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			if ((str[i] == 34 || str[i] == 39) && str[i - 1] != '\\')
			{
				quote = str[i++];
				while ((str[i] == quote && str[i - 1] == '\\') || str[i] != quote)
				{
					// ft_putchar_fd(str[i], 1);
					// printf("%d\n",index++);
					i++;
				}
			}
			i++;
		}
	}
	return (j);
}

static void *leak(char **spl, int j)
{
	j = j - 1;
	while (spl[j])
	{
		free(spl[j]);
		j--;
	}
	free(spl);
	return (NULL);
}

static int carcts(char *str)
{
	int i;
	int check_quote;
	char quote;

	i = 0;
	check_quote = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if ((str[i] == 34 || str[i] == 39) && str[i - 1] != '\\')
		{
			quote = str[i];
			i++;
			while ((str[i] == quote && str[i - 1] == '\\') || str[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

static char *alloc(char **tab, char *src)
{
	int i;
	int j;
	int o;
	char quote;

	j = 0;
	o = 0;
	while (src[o] == ' ' || src[o] == '\t')
		o++;
	while (j < words(src))
	{
		i = 0;
		if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o]) + 1))))
			return (leak(tab, j));
		while ((src[o] != '\t' && src[o] != ' ') && src[o])
		{
			if ((src[o] == 34 || src[o] == 39) && src[o - 1] != '\\')
			{
				quote = src[o];
				tab[j][i++] = src[o++];
				while ((src[o] == quote && src[o - 1] == '\\' )||src[o] != quote)
					tab[j][i++] = src[o++];
			}
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

char **ft_space_split_quote(char const *s)
{
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
