#include "minishell.h"

int stock(char c)
{
    ft_putendl_fd("samir not zwin", 1);
    return (1);
}
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
        if (ft_isalnum(c) == 0 && ( c == '|' || c == ';' ))
            return (0);
    }
    else if (operation == ';')
    {
        //3andi takhwwiiira hna
        if ((ft_isalnum(c) == 0 && c != '\0') && (c == '-' || c == '|' || c == ';' || c == '+'))
        {
            return (0);
        }
    }
    else if (operation == '<')
    {
        if (ft_isalnum(c) == 0 || c == '>' || c == '<' || c == '|' || c == ';')
            return (0);
    }
    else if (operation == '>')
    {
        if (ft_isalnum(c) == 0 && (c == '>' || c == '<' || c == '|' || c == ';'))
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
    t_line check;

    check_quote = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == '"')
        {
            if (check_quote == 0)
                check_quote = 1;
            else
                check_quote = 0;
        }
        if (line[i] == '|' && check_operation(&line[i]) == 0)
        {
            ft_putstr_fd("syntax error\n", 2);
            exit(1);
        }
        if (line[0] == ';' || (line[i] == ';' && check_operation(&line[i]) == 0))
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
    if (check_quote == 1)
    {
        ft_putstr_fd("syntax error\n", 2);
        exit(1);
    }
}

int check_what_after(char c)
{
    if (c != '/' && c != '\\' && c != '|' && c != '~' && c != '\n' && (c == '\'' || c == '"' || ft_isprint(c) == 1))
        return (1);
    return (0);
}

int check_redirection(char *line, int *i)
{
    if (line[*i] == '>' && line[*i + 1] == '>')
    {
        if (line[*i + 2] == '\0')
            return (*i == 0) ? (5) : (6);
        else if (check_what_after(line[*i + 2]) == 1)
            return (*i == 0) ? (7) : (8);
    }
    else if (line[*i] == '>')
    {
        if (line[*i + 1] == '\0')
            return (*i == 0) ? (1) : (2);
        else if (check_what_after(line[*i + 1]) == 1)
            return (*i == 0) ? (3) : (4);
    }
    else if (line[*i] == '<' && line[*i + 1] != '<')
    {
        if (line[*i + 1] == '\0')
            return (*i == 0) ? (9) : (10);
        else if (check_what_after(line[*i + 1]) == 1)
            return (*i == 0) ? (11) : (12);
    }
    // else
    // {
    //     ft_putstr_fd("\nerror 2\n", 2);
    //     exit(1);
    // }
    return (0);
}

int check_io_redirection(char *line, int *p, int *check_o_i)
{
    int redirection;

    redirection = check_redirection(line, p);
    if (redirection == 5 || redirection == 7 || redirection == 8 || redirection == 6)
        (*p)++;
    *check_o_i = redirection;
    if (redirection > 0)
        return (1);
    else
        return (0); //  kayna shi erreur
}

int check_type_element(char *line, int *check_i_o, int count)
{
    int i;
    int redirection;

    i = 0;
    redirection = -1;

    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
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
    while (l_cmd->command->tool.tab[l_cmd->command->tool.i])
    {
        l_cmd->command->tool.check_io = -1;
        l_cmd->command->tool.result = check_type_element(l_cmd->command->tool.tab[l_cmd->command->tool.i], &l_cmd->command->tool.check_io, l_cmd->command->tool.i);
        if (l_cmd->command->tool.result == 1 || l_cmd->command->tool.result == 6)
        {
            if (l_cmd->command->tool.cmd == 0)
            {
                alloc_affect(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i], 1);
            }
            else
            {
                alloc_affect(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i], 2);
            }
        }
        else if (l_cmd->command->tool.result >= 2 && l_cmd->command->tool.result <= 5)
            affect_redirection(l_cmd);
        l_cmd->command->tool.i++;
    }
    l_cmd->command->s_left = tmp;
}
