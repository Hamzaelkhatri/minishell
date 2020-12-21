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

// void print(t_list_cmd *l_command)
// {
//     t_list_cmd *tmp_l_command;
//     t_command *tmp_command;
//     t_simple_command *tmp_s;

//     tmp_l_command = l_command;
//     tmp_command = l_command->command;
//     tmp_s = l_command->command->s_left;
//     while (l_command->command->s_left != NULL)
//     {
//         if (l_command->command->s_left->l_element->indice == 1)
//             printf("|cmd  ==> %s|\n", l_command->command->s_left->l_element->cmd);
//         else if (l_command->command->s_left->l_element->indice == 2)
//             printf("|argument  ==> %s|\n", l_command->command->s_left->l_element->argument);
//         else if (l_command->command->s_left->l_element->indice == 3)
//             printf("|direction ==> %s|\t|redirection ==> %s|\n", l_command->command->s_left->l_element->redirection.i_o, l_command->command->s_left->l_element->redirection.file);
//         l_command->command->s_left = l_command->command->s_left->right;
//     }
//     l_command->command->s_left = tmp_s;
//     // l_command = tmp;
// }