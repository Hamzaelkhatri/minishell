
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int words(char *str, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] == c && str[i])
            i++;
        if (str[i] && str[i] != c)
        {
            i++;
            j++;
        }
        while (str[i] && str[i] != c)
            i++;
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

static int carcts(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
    {
        i++;
    }
    return (i);
}

static char *alloc(char **tab, char *src, char c)
{
    int i;
    int j;
    int o;

    j = 0;
    o = 0;
    while (src[o] == c)
        o++;
    while (j < words(src, c))
    {
        i = 0;
        if (!(tab[j] = malloc(sizeof(char) * (carcts(&src[o], c) + 1))))
            return (leak(tab, j));
        while (src[o] != c && src[o])
            tab[j][i++] = src[o++];
        tab[j][i] = '\0';
        while (src[o] == c && src[o])
            o++;
        j++;
    }
    tab[j] = NULL;
    return (*tab);
}

char **ft_split(char const *s, char c)
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

char *my_strcat(char *strg1, char *strg2)
{
    char *start;
    int i = 0;

    start = strdup(strg1);
    while (*strg1 != '\0')
    {
        strg1++;
    }

    while (*strg2 != '\0')
    {
        *strg1 = *strg2;
        strg1++;
        strg2++;
    }

    *strg1 = '\0';
    return start;
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (s1 && s2)
	{
		p = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
		if (p == NULL)
			return (NULL);
		while (s1[j])
		{
			p[i++] = s1[j++];
		}
		while (s2[k])
		{
			p[i++] = s2[k++];
		}
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}

char *ft_str_join(char *s1, char *s2, char *s3) {
  char *result;
  char *tmp;

  tmp = ft_strjoin(s1, s2);
  result = ft_strjoin(tmp, s3);
  return (result);
}
char *concat(char **tmp)
{
    int i;
    char *result;
    int len;
    int j;

    j = 0;
    i = 0;
    len = 0;
    result = strdup("\0");
    char *tmp1;
    tmp1 = strdup("\0");
    while (tmp[i] != NULL)
    {
        result = ft_str_join(tmp1," ",tmp[i]);
        tmp1 = strdup(result);
        i  = i +1;
    }
    return (result);
}

int main()
{
    char *str = "hello samir hamza hiba sara";
    int i = 0;
    char **tmp = ft_split(str, ' ');
    i = -1;
    // while (tmp[i + 1] != NULL)
    // {
    //     if( i == -1)
    //         i++;
    printf("==>|%s|\n", concat(tmp));
    // i++;
    //     i = i + 2;
    // }
    return (0);
}