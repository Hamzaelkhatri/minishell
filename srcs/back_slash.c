
#include "minishell.h"


void double_quotes(char *line, char **str, int *i, int *index)
{
	(*str)[*index] = line[++(*i)];
			while ((((line[*i] == 34 && count_antislach(line, *i - 1) == 0)) || line[*i] != 34) && line[*i])
			{
				if(line[*i] == '\\' && line[*i + 1] == '\\')
				{
					(*str)[++(*index)] = line[++(*i)];
					(*i)++;
				}
				else if ((line[*i] == '\\' && line[*i + 1] == 34))
					(*str)[*index] = line[++(*i)];
				else
					(*str)[++(*index)] = line[++(*i)];
			}
			(*str)[*index] = line[++(*i)];
}
char *ft_ignoring(char *line)
{
	int i;
	char wich;
	int tmp;
	int tmp1;
	int index;
	char *str;

	i = 0;
	index = 0;
	str = (char *)malloc(ft_strlen(line));
	while (line[i])
	{
		if (line[i] == 34 && count_antislach(line, i - 1))
		{
			str[index] = line[++i];
			while ((((line[i] == 34 && count_antislach(line, i - 1) == 0)) || line[i] != 34) && line[i])
			{
				if(line[i] == '\\' && line[i + 1] == '\\')
				{
					str[++index] = line[++i];
					i++;
				}
				else if ((line[i] == '\\' && line[i + 1] == 34))
					str[index] = line[++i];
				else
					str[++(index)] = line[++i];
			}
			str[index] = line[++i];
			// printf("str ==> {%s}\n",str);
			// double_quotes(line, &str, &i, &index);	
		}
		else if(line[i] == 39 && count_antislach(line, i - 1))
		{
			// printf("2\n");
			str[index] = line[++i];
			while(line[i] != 39)
				str[++index] = line[++i];
			str[index] = line[++i];
		}
		else if (line[i] == '\\')
		{
			// printf("2\n");
			str[index] = line[++i];
		}
		else
		str[index++] = line[i++];
		if(!line[i])
		str[index] = '\0'; 
		// str[++index] = line[++i];
	}
	// free(line);
	// line = NULL;
	return (str);
}
// "$PWD""$PW"D