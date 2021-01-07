#include "../includes/minishell.h"

void check_errors1(char *line)
{
    int i;
    char **sp_free;

    i = 0;
    sp_free = ft_space_split(line);
    while (line[i] != '\0')
    {
        if (check_revers_check(line[i], line[i + 1], '>', ';') == 1)
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if (check_revers_check(line[i], line[i + 1], '>', '|') == 1)
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if (check_revers_check(line[i], line[i + 1], '>', '<') == 1)
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (sp_free[i] != (void *)0)
    {
        if ((ft_strcmp(sp_free[i], "|") == 0 &&
             ft_strcmp(sp_free[i + 1], ">") == 0) ||
            (ft_strcmp(sp_free[i], ">") == 0 &&
             ft_strcmp(sp_free[i + 1], "|") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], ";") == 0 &&
             ft_strcmp(sp_free[i + 1], ">") == 0) ||
            (ft_strcmp(sp_free[i], ">") == 0 &&
             ft_strcmp(sp_free[i + 1], ";") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], ">") == 0) ||
            (ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], ">") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
}

void check_errors2(char *line)
{
    int i;
    char **sp_free;

    i = 0;
    sp_free = ft_space_split(line);
    while (line[i] != '\0')
    {
        if (check_revers_check(line[i], line[i + 1], '<', ';') == 1)
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if (check_revers_check(line[i], line[i + 1], '<', '|') == 1)
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if (check_revers_check(line[i], line[i + 1], '<', '>') == 1)
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if (line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>')
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (sp_free[i] != (void *)0)
    {
        if ((ft_strcmp(sp_free[i], "|") == 0 &&
             ft_strcmp(sp_free[i + 1], "<") == 0) ||
            (ft_strcmp(sp_free[i], "<") == 0 &&
             ft_strcmp(sp_free[i + 1], "|") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], ";") == 0 &&
             ft_strcmp(sp_free[i + 1], "<") == 0) ||
            (ft_strcmp(sp_free[i], "<") == 0 &&
             ft_strcmp(sp_free[i + 1], ";") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], "<") == 0) ||
            (ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], "<") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
}

void check_errors3(char *line)
{
    int i;
    char **sp_free;

    i = 0;
    sp_free = ft_space_split(line);
    while (line[i] != '\0')
    {
        if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '|') || (line[i] == '|' && line[i + 1] == '>' && line[i + 2] == '>'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == ';') || (line[i] == ';' && line[i + 1] == '>' && line[i + 2] == '>'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>') || (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '<'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>') || (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '<'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (sp_free[i] != (void *)0)
    {
        if ((ft_strcmp(sp_free[i], "|") == 0 &&
             ft_strcmp(sp_free[i + 1], ">>") == 0) ||
            (ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], "|") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], ";") == 0 &&
             ft_strcmp(sp_free[i + 1], ">>") == 0) ||
            (ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], ";") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], ">>") == 0) ||
            (ft_strcmp(sp_free[i], ">>") == 0 &&
             ft_strcmp(sp_free[i + 1], ">>") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
}

void check_seperator_errors(char *line)
{
    int i;
    char **sp_free;

    i = 0;
    sp_free = ft_space_split(line);
    while (line[i] != '\0')
    {
        if ((line[i] == '|' && line[i + 1] == ';') ||
            (line[i] == ';' && line[i + 1] == '|'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((line[i] == '|' && line[i + 1] == '|') ||
            (line[i] == ';' && line[i + 1] == ';'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (sp_free[i] != (void *)0)
    {
        if ((ft_strcmp(sp_free[i], "|") == 0 &&
             ft_strcmp(sp_free[i + 1], ";") == 0) ||
            (ft_strcmp(sp_free[i], ";") == 0 &&
             ft_strcmp(sp_free[i + 1], "|") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], "|") == 0 &&
             ft_strcmp(sp_free[i + 1], "|") == 0) ||
            (ft_strcmp(sp_free[i], ";") == 0 &&
             ft_strcmp(sp_free[i + 1], ";") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
}
void check_line_error(char *line)
{

    check_errors1(line);
    check_errors2(line);
    check_errors3(line);
    check_seperator_errors(line);
}