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

void alloc_affect(t_list_cmd *l_cmd, t_tool *tool, char *command, int indice)
{
    if (indice == 1)
    {
        tool->cmd = 1;
        l_cmd = add_simple_cmd(l_cmd, 1);
        if (l_cmd->s_left->right != NULL)
            l_cmd->s_left = l_cmd->s_left->right;
        l_cmd->s_left->l_element->cmd = ft_strdup(command);
    }
    else if (indice == 2)
    {
        l_cmd = add_simple_cmd(l_cmd, 2);
        if (l_cmd->s_left->right != NULL)
            l_cmd->s_left = l_cmd->s_left->right;
        l_cmd->s_left->l_element->argument = ft_strdup(command);
    }
    else if (indice == 3)
    {
        l_cmd = add_simple_cmd(l_cmd, 3);
        if (l_cmd->s_left->right != NULL)
            l_cmd->s_left = l_cmd->s_left->right;
        l_cmd->s_left->l_element->redirection.file = ft_strdup(command);
        if (wich_redirection(tool->check_io) == 2)
            l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">>");
        else if (wich_redirection(tool->check_io) == 1)
            l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">");
        else if (wich_redirection(tool->check_io) == 3)
            l_cmd->s_left->l_element->redirection.i_o = ft_strdup("<");
    }
}

void affect_redirection(t_tool *tool, t_list_cmd *l_cmd)
{
    char **tab_split;

    if (tool->result == 3 || tool->result == 4 || tool->result == 5)
    {
        if (wich_redirection(tool->check_io) == 2 || wich_redirection(tool->check_io) == 1)
            tab_split = ft_split(tool->tab[tool->i], '>');
        else
            tab_split = ft_split(tool->tab[tool->i], '<');
        if (tool->result == 3)
            alloc_affect(l_cmd, tool, tab_split[0], 3);
        else if (tool->result == 4 || tool->result == 5)
        {
            if (tool->cmd == 0)
                alloc_affect(l_cmd, tool, tab_split[0], 1);
            else
                alloc_affect(l_cmd, tool, tab_split[0], 2);
            if (tool->result == 4)
                alloc_affect(l_cmd, tool, tool->tab[++tool->i], 3);
            else if (tool->result == 5)
                alloc_affect(l_cmd, tool, tab_split[1], 3);
        }
    }
    if (tool->result == 2)
        alloc_affect(l_cmd, tool, tool->tab[++tool->i], 3);
}

void check_element(t_tool *tool, t_list_cmd *l_cmd)
{
    int check;
    t_simple_command *tmp;
    tool->i = 0;
    tmp = l_cmd->s_left;
    while (tool->tab[tool->i])
    {
        tool->check_io = -1;
        tool->result = check_type_element(tool->tab[tool->i], &tool->check_io, tool->i);
        if (tool->result == 1 || tool->result == 6)
        {
            if (tool->cmd == 0)
                alloc_affect(l_cmd, tool, tool->tab[tool->i], 1);
            else
                alloc_affect(l_cmd, tool, tool->tab[tool->i], 2);
        }
        else if (tool->result >= 2 && tool->result <= 5)
            affect_redirection(tool, l_cmd);
        tool->i++;
    }
    l_cmd->s_left = tmp;
}

void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    t_tool tool;
    t_list_cmd *tmp;

    ft_bzero(&tool, sizeof(t_tool));
    tmp = l_cmd;
    tool.tab = ft_space_split(s_command);
    // ft_putstr_fd("\n\nwa kelb\n\n", 1);
    if (l_cmd->right != NULL)
    {
        l_cmd = add_list_cmd(l_cmd);
    }
    while (l_cmd->right != NULL)
        l_cmd = l_cmd->right;
    check_element(&tool, l_cmd);
    l_cmd = tmp;
}

void parcs_simple_command(char *line, int *index, t_list_cmd *l_cmd, int y_or_n)
{
    char *s_command;
    int i;

    i = index[0];
    s_command = (char *)malloc(sizeof(char) * index[1]);
    printf("index[0] ==> %d\n", index[0]);
    while (i < index[1])
    {
        s_command[i] = line[i];
        i++;
    }
    printf("|%s|\n", s_command);
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
            // printf("|index[0] ===> %d|\n", index[0]);
            parcs_simple_command(line, index, l_cmd, k);
        }
        i++;
    }
    k = 0;
    index[1] = i;
    printf("%d\n", index[1]);
    parcs_simple_command(line, index, l_cmd, k);
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
    ft_check_line(line);
    l_command = add_list_cmd(l_command);
    parcs(line, l_command);
    if (l_command->s_left->l_element == NULL)
        ft_putstr_fd("minirt\n", 1);
    // l_command = l_command->right;
    // while (l_command->s_left != NULL)
    // {
    //     if (l_command->s_left->l_element->indice == 1)
    //         printf("|cmd  ==> %s|\n", l_command->s_left->l_element->cmd);
    //     else if (l_command->s_left->l_element->indice == 2)
    //         printf("|argument  ==> %s|\n", l_command->s_left->l_element->argument);
    //     else if (l_command->s_left->l_element->indice == 3)
    //         printf("|direction ==> %s|\t|redirection ==> %s|\n", l_command->s_left->l_element->redirection.i_o, l_command->s_left->l_element->redirection.file);
    //     l_command->s_left = l_command->s_left->right;
    // }
    return (0);
}
// i = check(line, &test);
// printf("|i==> %d|\t|\t %s \t|\n", i, test);
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);