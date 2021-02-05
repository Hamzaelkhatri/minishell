
#include "minishell.h"

static int words(char *str, char c)
{
	int i;
	int j;
	char quote;
	static int index;
	i = 0;
	j = 0;
	// printf("index{%d}\n",++index);
	while (str[i])
	{
		while ((str[i] == c && count_antislach(str, i - 1)) && str[i])
			i++;
		if (str[i] && str[i] != c)
			j++;
		while (str[i] && (((str[i] == c  && count_antislach(str, i - 1) == 0) || str[i] != c)))
		{
			if ((str[i] == 34 || str[i] == 39) && count_antislach(str, i - 1))
			{
				quote = str[i++];
				while (((quote == 34 && str[i] == quote && count_antislach(str, i - 1) == 0) || str[i] != quote) && str[i])
					i++;
				if (!str[i])
				{
					ft_putstr_fd("words\t",1);
					ft_putstr_fd("split_quotes",1);
					exit(1);
				}
			}
			if (str[i])
				i++;
		}
	}
	return (j);
}

static int carcts(char *str, char c)
{
	int i;
	char quote;

	i = 0;
	while (str[i] && (((str[i] == c  && count_antislach(str, i - 1) == 0) || str[i] != c)))
	{
		if ((str[i] == 34 || str[i] == 39) && count_antislach(str, i - 1))
		{
			quote = str[i];
			i++;
			while (((quote == 34 && str[i] == quote && count_antislach(str, i - 1) == 0) || str[i] != quote) && str[i])
				i++;
			if (!str[i])
			{
				ft_putstr_fd("split_quotes",1);
				// exit(1);
			}
		}
		if (str[i])
			i++;
	}
	return (i);
}

static void check_affec(char ***tab, char *src, int *o, int wich[2])
{
	int i;
	char quote;

	i = 0;
while (src[*o] && ((src[*o] == wich[1] && count_antislach(src, *o - 1) == 0) || src[*o] != wich[1]))
	{

		if ((src[*o] == 34 || src[*o] == 39) && count_antislach(src, *o - 1))
		{
			quote = src[*o];
			(*tab)[wich[0]][i++] = src[(*o)++];
			while (((quote == 34 && src[*o] == quote && count_antislach(src, *o - 1) == 0) || src[*o] != quote) && src[*o])
				(*tab)[wich[0]][i++] = src[(*o)++];
		}
		if (!src[*o])
		{
			ft_putstr_fd("split_quotes",1);
			// exit(1);
		}
		(*tab)[wich[0]][i++] = src[(*o)++];
	}
	(*tab)[wich[0]][i] = '\0';
}

static char *alloc(char **tab, char *src, char c)
{
	int wich[2];
	int j;
	int o;
	char quote;

	j = 0;
	o = 0;
	while (src[o] == c)
		o++;
	while (j < words(src, c))
	{
		if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o], c) + 1))))
			return (leak(tab, j));
		wich[0] = j;
		wich[1] = c;
		check_affec(&tab, src, &o, wich);
		while (src[o] == c && src[o])
			o++;
		j++;
	}
	tab[j] = NULL;
	return (*tab);
}

char **ft_split_quotes(char const *s, char c)
{
	int j;
	char **tab;
	char *str;

	j = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	tab = malloc(sizeof(char *) * (words(str, c) + 1));
	if (!tab)
		return (NULL);
	tab[j] = alloc(tab, str, c);
	return (tab);
}
