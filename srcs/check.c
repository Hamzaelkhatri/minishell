#include "minishell.h"

static int check_is_correct(char operation, char *line)
{
    int i;
    char c;

    i = 0;
    while (line[i] == ' ' && line[i] == '\t' && line[i])
        i++;
    c = line[i];
    if (operation == '|')
    {
        if (ft_isalnum(c) == 0 || c == '>' || c == '<' || c == '-' || c == '|' || c == ';' || c == '+')
            return (0);
    }
    else if (operation == ';')
    {
        if (ft_isalnum(c) == 0 || c == '>' || c == '<' || c == '-' || c == '|' || c == ';' || c == '+')
            return (0);
    }
    else if (operation == '<')
    {
        if (ft_isalnum(c) == 0 || c == '>' || c == '<' || c == '|' || c == ';')
            return (0);
    }
    else if (operation == '>')
    {
        ft_putstr_fd("fena asat\n", 1);
        if (ft_isalnum(c) == 0 || c == '>' || c == '<' || c == '|' || c == ';')
            return (0);
    }
    return (1);
}

static int check_operation(char *line)
{
    // printf("\n|c ==> %c|\n", line[0]);
    if (line[0] == '|')
    {
        if (check_is_correct(line[0], &line[1]) == 0)
            return (0);
    }
    else if (line[0] == ';')
    {
        if (check_is_correct(line[0], &line[1]) == 0)
            return (0);
    }
    else if (line[0] == '>')
    {
        if (line[1] == '>')
        {
            if (check_is_correct(line[0], &line[2]) == 0)
            {
                return (0);
            }
        }
        else if (line[0] == '>')
            if (check_is_correct(line[0], &line[1]) == 0)
                return (0);
    }
    else if (line[0] == '<')
    {
        if (check_is_correct(line[0], &line[1]) == 0)
            return (0);
    }
    return (1);
}
void ft_check_line(char *line)
{
    int i;
    t_line check;

    i = 0;
    while (line[i])
    {
        if (line[i] == '|' && check_operation(&line[i]) == 0)
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        if (line[i] == ';' && check_operation(&line[i]) == 0)
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        else if (line[i] == '<' && check_operation(&line[i]) == 0)
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        else if (line[i] == '>' && check_operation(&line[i]) == 0)
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        if (line[i] == '>' && line[i + 1] == '>')
            i++;
        i++;
    }
}