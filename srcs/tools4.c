#include "minishell.h"

long long ft_atoi_long(char *str)
{
    int i;
    int sign;
    long long result;
    int counter;

    i = 0;
    sign = 1;
    result = 0;
    counter = 0;

    while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n' || str[i] == '\v' || str[i] == '\t')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1 * sign;
        i++;
    }
    while (str[i] == '0')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0';
        i++;
        counter++;
    }
    return (result * sign);
}

void print_err_exite(char *s)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(s, 2);
    ft_putendl_fd(": numeric argument required", 2);
}

int is_int(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int count_digit(char *str)
{
    int i = 0;
    int c = 0;
    while (str[i] == '0')
        i++;
    while (str[i])
    {
        c++;
        i++;
    }
    return (c);
}

int size_args(t_command *l_cmd)
{
    int i;
    t_simple_command *tmp;

    tmp = l_cmd->s_left->right;
    i = 0;
    while (tmp)
    {
        i++;
        tmp = tmp->right;
    }
    return (i);
}