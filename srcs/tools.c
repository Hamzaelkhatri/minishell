#include "minishell.h"

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}

int check(char *line, char **test)
{
    int i;
    int count;
    int j;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == ';' || line[i] == '|')
            count++;
        i++;
    }
    if (count > 0)
    {
        i = 0;
        j = 0;
        *test = malloc((sizeof(char) * count) + 1);
        while (line[i])
        {
            if (line[i] == ';' || line[i] == '|')
                test[0][j++] = line[i];
            i++;
        }
        test[0][j] = '\0';
    }
    return (count);
}
int is_correct(char c)
{
    if (ft_isalnum(c) == 0 && c != '>' && c != '<' && c != '-' && c != '|' && c != ';' && c != ' ' && c != '\t')
    {
        return (0);
    }
    return (1);
}
