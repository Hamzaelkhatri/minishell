#include "minishell.h"

char *word_tolower(char *str)
{
    int i;
    char *ptr;

    i = 0;
    ptr = malloc(sizeof(char) * ft_strlen(str));
    while (str[i])
    {
        ptr[i] = ft_tolower(str[i]);
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
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

int check_int(char *str)
{
    int i;

    i = 0;
    str = ft_strtrim(str, "\n");
    str = ignoring_quote(str);
    while (str[i] && str[i] < 33)
        i++;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (ft_atoi_long(str) <= LLONG_MIN && str[i - 1] != '-')
    {
        print_err_exite(str);
        return (255);
    }
    if (ft_atoi_long(str) < LLONG_MIN)
    {
        print_err_exite(str);
        return (0);
    }
    else if (ft_atoi_long(str) > LLONG_MAX)
    {
        print_err_exite(str);
        return (255);
    }
    else if (ft_atoi_long(str) <= LONG_MIN && count_digit(&str[i]) == 19)
    {
        return (0);
    }
    else if (count_digit(&str[i]) == 19 && str[i - 1] == '-')
    {
        print_err_exite(str);
        return (255);
    }
    while (str[i])
    {

        if ((!ft_isdigit(str[i]) && str[i] != 32 && str[i] != '\t') || count_digit(&str[i]) > 19)
        {
            print_err_exite(str);
            return (255);
        }
        i++;
    }
    return (ft_atoi(str));
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

void commandes(char *cmd, t_path *path, t_command *l_cmd)
{
    if (!ft_strncmp(cmd, "$", 1) && get_var_env(path, cmd))
    {
        cmd = get_var_env(path, cmd);
    }
    if (!ft_strcmp("exit", word_tolower(cmd)))
        cmd = word_tolower(cmd);
    if (!ft_strcmp(cmd, "$?"))
    {
        ft_putendl_fd(ft_itoa(path->dollar), 1);
    }
    else if (!ft_strcmp(cmd, "pwd"))
    {
        if (size_args(l_cmd) >= 1 && !l_cmd->s_left->right->l_element->redirection.i_o)
        {
            ft_putendl_fd("pwd: too many arguments", 1);
            path->dollar = 0;
        }
        else
        {
            print_working_directory(path);
            path->dollar = 1;
        }
    }
    else if (!ft_strcmp(cmd, "env"))
    {
        show_env(path->env->fullenv);
        path->dollar = 1;
    }
    else if (!ft_strcmp(cmd, "cd"))
    {
        if (l_cmd->s_left->right != NULL)
            cd_cmd(l_cmd->s_left->right->l_element->argument, path);
        else
            cd_cmd(NULL, path);
        path->dollar = 1;
    }
    else if (!ft_strcmp(cmd, "exit"))
    {
        if (size_args(l_cmd) > 1 && is_int(l_cmd->s_left->right->l_element->argument))
        {
            ft_putendl_fd("minishell: exit: too many arguments", 2);
            exit(EXIT_FAILURE);
        }
        if (l_cmd->s_left->right && l_cmd->s_left->right->l_element->argument)
        {
            ft_putendl_fd("exit", 2);
            exit(check_int(l_cmd->s_left->right->l_element->argument));
        }
        else
        {
            ft_putendl_fd("exit", 2);
            exit(EXIT_SUCCESS);
        }
    }
    else if (!ft_strcmp(cmd, "export") && l_cmd->s_left->right == NULL)
    {
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_export(tmp);
        path->dollar = 1;
    }
    else if (!ft_strcmp(cmd, "export") && l_cmd->s_left->right != NULL)
    {
        while (l_cmd->s_left->right)
        {
            if (!export_cmd(l_cmd->s_left->right->l_element->argument, path->env->fullenv))
                break;
            l_cmd->s_left->right = l_cmd->s_left->right->right;
        }
    }
    else if (!ft_strcmp(cmd, "unset") && l_cmd->s_left->right != NULL)
    {
        unset_cmd(l_cmd->s_left->right->l_element->argument, path);
    }
    else if (!ft_strcmp(cmd, "echo"))
    {
        if (l_cmd->s_left->right)
            if (!ft_strcmp(l_cmd->s_left->right->l_element->argument, "-n\n"))
            {
                cmd = ft_strjoin(cmd, " -n");
                l_cmd->s_left->right = l_cmd->s_left->right->right;
            }
        while (l_cmd->s_left->right)
        {
            echo(l_cmd->s_left->right->l_element->argument, path);
            l_cmd->s_left->right = l_cmd->s_left->right->right;
            if (l_cmd->s_left->right)
                ft_putstr_fd(" ", 1);
        }
        if (ft_strcmp(cmd, "echo -n"))
            ft_putendl_fd("", 1);
    }
}

int get_cmd_(char *cmd, t_path *path, t_command *l_cmd)
{
    char *cmds;

    cmd = ft_strtrim(cmd, "\n");

    if ((l_cmd->s_left->right && l_cmd->s_left->right->l_element->redirection.i_o && l_cmd->s_left->l_element->cmd))
    {
        while (l_cmd->s_left->right)
        {
            if (l_cmd->s_left->right->l_element->redirection.i_o)
                shift_extra(l_cmd->s_left->right->l_element->redirection.file, l_cmd->s_left->right->l_element->redirection.i_o, path, l_cmd);
            l_cmd->s_left->right = l_cmd->s_left->right->right;
        }
    }
    else if (l_cmd->s_left->l_element->redirection.i_o)
    {
        while (l_cmd->s_left)
        {
            if (l_cmd->s_left->l_element->redirection.file)
                 shift_extra(l_cmd->s_left->l_element->redirection.file, l_cmd->s_left->l_element->redirection.i_o, path, l_cmd);
            l_cmd->s_left = l_cmd->s_left->right;
        }
    }
    else if (cmdcheck(cmd))
        commandes(cmd, path, l_cmd);
    else
    {
        if (!ft_strnstr(cmd, "$", 1) && search_env(path->env->fullenv, cmd))
        {
            cmd = get_var_env(path, cmd);
            l_cmd->s_left->l_element->cmd = ft_strdup(cmd);
        }
        cmds = ft_strjoin_command(l_cmd->s_left);
        // puts(cmds);
        getprogramme(path, cmds);
        wait(0);
    }
    wait(0);
    return 0;
}