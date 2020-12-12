#include "minishell.h"

t_simple_command *add_node(t_simple_command *node)
{
    t_simple_command *tmp;
    t_simple_command *new;

    tmp = node;
    if (!(new = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    new->left = NULL;
    new->parent = NULL;
    if (node == NULL)
        return (new);
    while (tmp->left != NULL)
    {
        new->parent = tmp;
        tmp = tmp->left;
    }
    tmp->left = new;
    return (node);
}

t_simple_command *add_data(char *word)
{
    t_simple_command *command;
    command = (t_simple_command *)malloc(sizeof(t_simple_command));
    command->element.word = strdup(word);
    return (command);
}

t_list_cmd *add_list_cmd(t_list_cmd *parent)
{
    t_list_cmd *tmp;
    t_list_cmd *new;

    if (parent == NULL)
    {
        if (!(parent = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
            return (NULL);
        parent->s_command = NULL;
        parent->separator = 0;
        parent->next = NULL;
    }
    tmp = parent;
    if (!(new = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
        return (NULL);
    new->s_command = NULL;
    new->separator = 0;
    new->next = NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return (parent);
}

// t_check check_type_element(char *line, t_check *check)
// {
//     int i;

//     i = 0;
//     while (line[i])
//     {
//         if (line[i] == '>' || line[i] == '<')
//             check->redirection = check->word  + check->redirection + 1;
//         else if (line[i])
//             i++;
//     }
// }
// void check_element(char **tab, t_list_cmd *l_cmd, t_check *check)
// {
//     int i;
//     t_check check;

//     ft_bzero(&check, sizeof(t_check));
//     i = 0;
//     while (tab[i])
//     {
//         check_type_element(tab[i], &check);
//     }
// }
void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    char **tab;
    t_check check;
    t_list_cmd *tmp;

    tmp = l_cmd;
    ft_bzero(&check, sizeof(t_check));
    tab = ft_space_split(s_command);
    // printf("%s\n", tab[0]);

    // check_element(tab, l_cmd, &check);
    l_cmd = add_list_cmd(l_cmd);
    // while (l_cmd)
    //     l_cmd = l_cmd->next;
}

void parcs_simple_command(char *line, int count, t_list_cmd *l_cmd, int y_or_n)
{
    char *s_command;
    int i;

    i = 0;
    if (line[count + 1] == '|' || line[count + 1] == ';')
    {
        ft_putstr_fd("u must enter just one controle operator\n", 2);
        exit(1);
    }
    s_command = (char *)malloc(sizeof(char) * count);
    while (i < count)
    {
        s_command[i] = line[i];
        i++;
    }
    s_command[i] = '\0';
    // printf("%s\n", s_command);
    parcs_this_simple_command(s_command, l_cmd, line[i], y_or_n);
}

void parcs(char *line, t_list_cmd *l_cmd)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (line[i])
    {
        if (is_correct(line[i]) == 0)
        {
            ft_putstr_fd("error 1", 2);
            exit(1);
        }
        if (line[i] == '|' || line[i] == ';')
        {
            k++;
            parcs_simple_command(line, i, l_cmd, k);
        }
        i++;
    }
    parcs_simple_command(line, i, l_cmd, k);
}
int main()
{
    int fd;
    t_list_cmd *l_command;
    l_command = NULL;
    fd = open("command.txt", O_RDWR);
    char *line;
    char *test;
    int i = 0;
    get_next_line(fd, &line);
    parcs(line, l_command);
    return (0);
}
// i = check(line, &test);
// printf("|i==> %d|\t|\t %s \t|\n", i, test);
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);