#include "minishell.h"

char **input_or_output(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '>')
            return (ft_split(line, '>'));
        else if (line[i] == '<')
            return (ft_split(line, '<'));
        i++;
    }
    return (NULL);
}

void alloc_affect(t_list_cmd *l_cmd, char *command, int indice)
{
    if (indice == 1)
    {
        l_cmd->tool.cmd = 1;
        l_cmd = add_simple_cmd(l_cmd, 1);
        if (l_cmd->s_left->right != NULL)
            l_cmd->s_left = l_cmd->s_left->right;
        l_cmd->s_left->l_element->cmd = ft_strdup(command);
    }
    else if (indice == 2)
    {
        l_cmd->tool.argument = 2;
        l_cmd = add_simple_cmd(l_cmd, 2);
        if (l_cmd->s_left->right != NULL)
            l_cmd->s_left = l_cmd->s_left->right;
        l_cmd->s_left->l_element->argument = ft_strdup(command);
    }
    else if (indice == 3)
    {
        l_cmd->tool.argument = 3;
        l_cmd = add_simple_cmd(l_cmd, 3);
        if (l_cmd->s_left->right != NULL)
            l_cmd->s_left = l_cmd->s_left->right;
        l_cmd->s_left->l_element->redirection.file = ft_strdup(command);
        if (wich_redirection(l_cmd->tool.check_io) == 2)
            l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">>");
        else if (wich_redirection(l_cmd->tool.check_io) == 1)
            l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">");
        else if (wich_redirection(l_cmd->tool.check_io) == 3)
            l_cmd->s_left->l_element->redirection.i_o = ft_strdup("<");
    }
}

void affect_redirection(t_list_cmd *l_cmd)
{
    char **tab_split;
    int result;

    result = l_cmd->tool.result;
    if (result == 3 || result == 4 || result == 5)
    {
        if (wich_redirection(l_cmd->tool.check_io) == 2 || wich_redirection(l_cmd->tool.check_io) == 1)
            tab_split = ft_split(l_cmd->tool.tab[l_cmd->tool.i], '>');
        else
            tab_split = ft_split(l_cmd->tool.tab[l_cmd->tool.i], '<');
        if (result == 3)
            alloc_affect(l_cmd, tab_split[0], 3);
        else if (result == 4 || result == 5)
        {
            if (l_cmd->tool.cmd == 0)
                alloc_affect(l_cmd, tab_split[0], 1);
            else
                alloc_affect(l_cmd, tab_split[0], 2);
            if (result == 4)
                alloc_affect(l_cmd, l_cmd->tool.tab[++l_cmd->tool.i], 3);
            else if (result == 5)
                alloc_affect(l_cmd, tab_split[1], 3);
        }
    }
    if (result == 2)
        alloc_affect(l_cmd, l_cmd->tool.tab[++l_cmd->tool.i], 3);
}

void check_element(t_list_cmd *l_cmd)
{
    int check;
    t_simple_command *tmp;
    l_cmd->tool.i = 0;
    tmp = l_cmd->s_left;
    while (l_cmd->tool.tab[l_cmd->tool.i])
    {
        l_cmd->tool.check_io = -1;
        l_cmd->tool.result = check_type_element(l_cmd->tool.tab[l_cmd->tool.i], &l_cmd->tool.check_io, l_cmd->tool.i);
        if (l_cmd->tool.result == 1 || l_cmd->tool.result == 6)
        {
            if (l_cmd->tool.cmd == 0)
                alloc_affect(l_cmd, l_cmd->tool.tab[l_cmd->tool.i], 1);
            else
                alloc_affect(l_cmd, l_cmd->tool.tab[l_cmd->tool.i], 2);
        }
        else if (l_cmd->tool.result >= 2 && l_cmd->tool.result <= 5)
            affect_redirection(l_cmd);
        l_cmd->tool.i++;
    }
    l_cmd->s_left = tmp;
}

void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    t_list_cmd *tmp;

    // ft_bzero(&tool, sizeof(t_tool));
    tmp = l_cmd;
    l_cmd->tool.tab = ft_space_split(s_command);
    if (l_cmd->s_left->l_element != NULL)
        l_cmd = add_list_cmd(l_cmd);
    while (l_cmd->right != NULL)
        l_cmd = l_cmd->right;
    check_element(l_cmd);
    l_cmd = tmp;
}

void parcs_simple_command(char *line, int *index, t_list_cmd *l_cmd, int y_or_n)
{
    char *s_command;
    int i;
    int k;

    k = 0;
    i = index[0];
    s_command = (char *)malloc(sizeof(char) * index[1]);
    while (i < index[1])
    {
        s_command[k] = line[i];
        i++;
        k++;
    }
    s_command[i] = '\0';
    index[0] = ++i;
    parcs_this_simple_command(s_command, l_cmd, line[i], y_or_n);
    free(s_command);
}

void parcs(char *line, t_list_cmd *l_cmd)
{
    int i;
    int k;
    int index[2];

    k = 0;
    i = 0;
    index[0] = 0;
    while (line[i])
    {
        if (is_correct(line[i]) == 0)
        {
            ft_putstr_fd("error 1", 2);
            exit(1);
        }
        if (line[i] == '|' || line[i] == ';')
        {
            k = 1;
            index[1] = i;
            parcs_simple_command(line, index, l_cmd, k);
        }
        i++;
    }
    k = 0;
    index[1] = i;
    parcs_simple_command(line, index, l_cmd, k);
}

void print_list(t_list_cmd *l_command)
{
    t_list_cmd *tmp;

    tmp = l_command;
    while (l_command->s_left != NULL)
    {
        if (l_command->s_left->l_element->indice == 1)
            printf("|cmd  ==> %s|\n", l_command->s_left->l_element->cmd);
        else if (l_command->s_left->l_element->indice == 2)
            printf("|argument  ==> %s|\n", l_command->s_left->l_element->argument);
        else if (l_command->s_left->l_element->indice == 3)
            printf("|direction ==> %s|\t|redirection ==> %s|\n", l_command->s_left->l_element->redirection.i_o, l_command->s_left->l_element->redirection.file);
        l_command->s_left = l_command->s_left->right;
    }
    l_command = tmp;
}
int main()
{
    int fd;
    t_list_cmd *l_command;
    l_command = NULL;
    fd = open("command.txt", O_RDWR);
    char *line;
    get_next_line(fd, &line);
    ft_check_line(line);
    if (line[0] == '\0')
        return (0);
    l_command = add_list_cmd(l_command);
    parcs(line, l_command);

    sort(l_command);
    print_list(l_command);
    return (0);
}
// i = check(line, &test);
// printf("|i==> %d|\t|\t %s \t|\n", i, test);
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);