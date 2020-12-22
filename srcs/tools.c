#include "minishell.h"

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}

int ft_2strlen(char **str)
{
    int i;

    i = 0;
    while (str[i] != 0)
        i++;
    return (i);
}

char *ft_str_in_str(const char *s1, const char *s2)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    if (!s2[j])
        return ((char *)s1);
    while (s1[i])
    {
        j = 0;
        if (s1[i] == s2[j])
        {
            j = 1;
            while (s2[j] && s2[j] == s1[i + j])
                j++;
            if (!s2[j] && !s1[i + j])
                return ((char *)&s1[i]);
        }
        i++;
    }
    return (NULL);
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
    if (ft_isalnum(c) == 0 && c != '"' && c != '\'' && c != '>' && c != '<' && c != '-' && c != '|' && c != ';' && c != ' ' && c != '\t')
    {
        return (0);
    }
    return (1);
}

void ft_wich(t_check *wich, int number)
{
    if (number == 1)
        wich->cmd = wich->cmd + wich->word + wich->redirection + 1;
    else if (number == 2)
        wich->word = wich->cmd + wich->word + wich->redirection + 1;
    else if (number == 3)
        wich->redirection = wich->cmd + wich->word + wich->redirection + 1;
}

void print(t_list_cmd *l_command)
{
    t_list_cmd *tmp_l_command;
    t_command *tmp_command;
    t_simple_command *tmp_s;

    tmp_l_command = l_command;
    tmp_command = l_command->command;
    tmp_s = l_command->command->s_left;
    while (l_command != NULL)
    {
        tmp_command = l_command->command;
        tmp_s = l_command->command->s_left;
        while (l_command->command != NULL)
        {
            tmp_s = l_command->command->s_left;
            while (l_command->command->s_left != NULL)
            {
                if (l_command->command->s_left->l_element->indice == 1)
                    printf("|cmd  ==> %s|\n", l_command->command->s_left->l_element->cmd);
                else if (l_command->command->s_left->l_element->indice == 2)
                    printf("|argument  ==> %s|\n", l_command->command->s_left->l_element->argument);
                else if (l_command->command->s_left->l_element->indice == 3)
                    printf("|direction ==> %s|\t|redirection ==> %s|\n", l_command->command->s_left->l_element->redirection.i_o, l_command->command->s_left->l_element->redirection.file);
                l_command->command->s_left = l_command->command->s_left->right;
            }
            l_command->command->s_left = tmp_s;
            l_command->command = l_command->command->right;
        }
        ft_putendl_fd("--------- command2 ----------", 1);
        l_command->command = tmp_command;
        l_command = l_command->next;
    }
    // l_command->command->s_left = tmp_s;
    l_command = tmp_l_command;

    // l_command = tmp;
}
int count_line(char **env)
{
    int i = 0;
    if (!env)
        return (0);
    while (env[i])
        i++;
    return (i);
}

int search_str(char *str1, char *str2, int l1, int l2)
{
    int i;
    i = 0;

    if (l1 != l2 || l1 == 0 || l2 == 0)
        return (0);
    else if (ft_strncmp(str1, str2, l1) == 0)
        return (1);
    return (0);
}
