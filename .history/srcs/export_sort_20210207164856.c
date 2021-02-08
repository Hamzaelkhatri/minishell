#include "minishell.h"

char **ft_strdup_extra(char **str)
{
	char **ptr;
	int i;

	if(!(ptr = malloc(sizeof(char *) * count_line(str))))
		return NULL;
	i = 0;
	while(str[i+1])
	{
		ptr[i] = ft_strdup(str[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

void ft_sortstr(char **str)
{
	int i;
	int j;
	int count;
	char *tmp;
	char *temp;

	i = 0;
	count = count_line(str);
	while(i<=count && str[i])
	{
		j = i;
		while(++j<=count && str[j])
		{
			if(ft_memcmp(str[i],str[j],ft_strlen(str[j]))>0)
			{
				temp = ft_strdup(str[i]);
				tmp = str[i];
				str[i] = ft_strdup(str[j]);
				// frees(&tmp);
				tmp = str[j];
				str[j] = ft_strdup(temp);
				// frees(&tmp);
				// frees(&temp);
			}
		}
		i++;
	}
}
