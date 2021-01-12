#include "minishell.h"

static int check_is_correct(char operation, char *line)
{
    int i;
    char c;

    i = 0;
    while ((line[i] == ' ' || line[i] == '\t') && line[i])
        i++;
    c = line[i];
    if (operation == '|')
    {
        if (ft_isalnum(c) == 0 && (c == '|' || c == ';'))
            return (0);
    }
    else if (operation == ';')
    {
        if ((ft_isalnum(c) == 0 && c != '\0') && (c == '-' || c == '|' || c == ';' || c == '+'))
        {
            return (0);
        }
    }
    else if (operation == '<')
    {
        if ((ft_isalnum(c) == 0) && (c == '\0' || c == '>' || c == '<' || c == '|' || c == ';'))
            return (0);
    }
    else if (operation == '>')
    {
        if (ft_isalnum(c) == 0 && (c == '\0' || c == '>' || c == '<' || c == '|' || c == ';'))
            return (0);
    }
    return (1);
}

static int check_operation(char *line)
{
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
                return (0);
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
    int check_quote;
    char quotes;

    i = 0;
    while (line[i])
    {
        if (line[i] == ':')
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        if ((line[i] == '"' || line[i] == 39) && line[i - 1] != '\\')
        {
            quotes = line[i++];
            while (line[i] != quotes && line[i])
                i++;
            
            if (!(line[i]))
            {
                ft_putstr_fd("syntax error\n", 2);
                exit(1);
            }
        }
        else if (line[0] == '|' || (line[i] == '|' && check_operation(&line[i]) == 0))
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        else if (line[0] == ';' || (line[i] == ';' && check_operation(&line[i]) == 0))
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
        else if (line[i] == '>' && line[i + 1] == '>')
            i++;
        i++;
    }
}

int check_type_element(char *line, int *check_i_o, int count)
{
    int i;
    int redirection;
    int quotes;

    i = 0;
    quotes = 0;
    redirection = -1;

    while (line[i])
    {
        if (line[i] == 34 || line[i] == 39)
            quotes = (quotes == 0) ? 1 : 0;
        if ((line[i] == '>' || line[i] == '<') && quotes == 0)
            redirection = check_io_redirection(line, &i, check_i_o);
        i++;
    }
    if (count == 0 && redirection == -1)
        return (1);
    else if (redirection == 1 && (*check_i_o == 1 || *check_i_o == 5 || *check_i_o == 9)) // '\0' 3 >>
        return (2);
    else if (redirection == 1 && (*check_i_o == 3 || *check_i_o == 7 || *check_i_o == 11)) //
        return (3);
    else if (redirection == 1 && (*check_i_o == 2 || *check_i_o == 6 || *check_i_o == 10)) //
        return (4);
    else if (redirection == 1 && (*check_i_o == 4 || *check_i_o == 8 || *check_i_o == 12)) //
        return (5);                                                                        // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (count != 0 && redirection == -1)
        return (6);
    return (7);
}

void check_element(t_list_cmd *l_cmd)
{
    int check;
    t_simple_command *tmp;
    l_cmd->command->tool.i = 0;
    tmp = l_cmd->command->s_left;
    static int i = 0;
    while (l_cmd->command->tool.tab[l_cmd->command->tool.i])
    {
        l_cmd->command->tool.check_io = -1;
        l_cmd->command->tool.result = check_type_element(l_cmd->command->tool.tab[l_cmd->command->tool.i], &l_cmd->command->tool.check_io, l_cmd->command->tool.i);
        if (l_cmd->command->tool.result == 1 || l_cmd->command->tool.result == 6)
        {
            if (l_cmd->command->tool.cmd == 0)
                alloc_affect(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i], 1);
            else
                alloc_affect(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i], 2);
        }
        else if (l_cmd->command->tool.result >= 2 && l_cmd->command->tool.result <= 5)
            affect_redirection(l_cmd);
        l_cmd->command->tool.i++;
    }
    l_cmd->command->s_left = tmp;
}

int check_what_after(char c)
{
    if (c != '/' && c != '\\' && c != '|' && c != '~' && c != '\n' && (c == '\'' || c == '"' || ft_isprint(c) == 1))
        return (1);
    return (0);
}
