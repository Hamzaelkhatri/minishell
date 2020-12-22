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
        l_cmd->command->tool.cmd = 1;
        l_cmd->command = add_simple_cmd(l_cmd->command, 1);
        if (l_cmd->command->s_left->right != NULL)
            l_cmd->command->s_left = l_cmd->command->s_left->right;
        l_cmd->command->s_left->l_element->cmd = ft_strdup(command);
    }
    else if (indice == 2)
    {
        l_cmd->command->tool.argument = 2;
        l_cmd->command = add_simple_cmd(l_cmd->command, 2);
        if (l_cmd->command->s_left->right != NULL)
            l_cmd->command->s_left = l_cmd->command->s_left->right;
        l_cmd->command->s_left->l_element->argument = ft_strdup(command);
    }
    else if (indice == 3)
    {
        l_cmd->command->tool.argument = 3;
        l_cmd->command = add_simple_cmd(l_cmd->command, 3);
        if (l_cmd->command->s_left->right != NULL)
            l_cmd->command->s_left = l_cmd->command->s_left->right;
        l_cmd->command->s_left->l_element->redirection.file = ft_strdup(command);
        if (wich_redirection(l_cmd->command->tool.check_io) == 2)
            l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup(">>");
        else if (wich_redirection(l_cmd->command->tool.check_io) == 1)
            l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup(">");
        else if (wich_redirection(l_cmd->command->tool.check_io) == 3)
            l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup("<");
    }
}

void affect_redirection(t_list_cmd *l_cmd)
{
    char **tab_split;
    int result;
    result = l_cmd->command->tool.result;
    if (result == 3 || result == 4 || result == 5)
    {
        if (wich_redirection(l_cmd->command->tool.check_io) == 2 || wich_redirection(l_cmd->command->tool.check_io) == 1)
            tab_split = ft_split(l_cmd->command->tool.tab[l_cmd->command->tool.i], '>');
        else
            tab_split = ft_split(l_cmd->command->tool.tab[l_cmd->command->tool.i], '<');
        if (result == 3)
            alloc_affect(l_cmd, tab_split[0], 3);
        else if (result == 4 || result == 5)
        {
            if (l_cmd->command->tool.cmd == 0)
                alloc_affect(l_cmd, tab_split[0], 1);
            else
                alloc_affect(l_cmd, tab_split[0], 2);
            if (result == 4)
                alloc_affect(l_cmd, l_cmd->command->tool.tab[++l_cmd->command->tool.i], 3);
            else if (result == 5)
                alloc_affect(l_cmd, tab_split[1], 3);
        }
    }
    if (result == 2)
        alloc_affect(l_cmd, l_cmd->command->tool.tab[++l_cmd->command->tool.i], 3);
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

void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    t_command *tmp_command;
    int i = 0;
    tmp_command = l_cmd->command;
    if (l_cmd->command->s_left->l_element != NULL)
        l_cmd->command = add_command(l_cmd->command);
    while (l_cmd->command->right != NULL)
        l_cmd->command = l_cmd->command->right;
    ft_bzero(&l_cmd->command->tool, sizeof(t_tool));
    l_cmd->command->tool.tab = ft_space_split(s_command);
    // while (l_cmd->command->tool.tab[i])
    // {
    //     printf("hak o ara ==>  %s|\n", l_cmd->command->tool.tab[i++]);
    // }
    // // printf("--------------------\n");
    check_element(l_cmd);
    l_cmd->command = tmp_command;
}

void parcs_simple_command(char *line, int *index, t_list_cmd *l_cmd, int y_or_n)
{
    char *s_command;
    int i;
    int k;

    k = 0;
    i = index[0];
    s_command = (char *)malloc(sizeof(char) * (index[1] - i));
    while (i < index[1])
    {
        s_command[k] = line[i];
        i++;
        k++;
    }
    s_command[k] = '\0';
    index[0] = ++i;
    parcs_this_simple_command(s_command, l_cmd, line[i], y_or_n);
    free(s_command);
}

void parse_command(t_list_cmd *l_cmd, char *line)
{
    int i;
    int k;
    int index[2];
    t_list_cmd *tmp;

    k = 0;
    i = 0;
    index[0] = 0;
    tmp = l_cmd;
    if (l_cmd->command->s_left->l_element != NULL)
        l_cmd = add_list_cmd(l_cmd);
    while (l_cmd->next != NULL)
        l_cmd = l_cmd->next;
    while (line[i])
    {
        if (is_correct(line[i]) == 0)
        {
            ft_putstr_fd("error 1", 2);
            exit(1);
        }
        if (line[i] == '|')
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
    l_cmd = tmp;
}

int check_parse_list_command(char *line, int i)
{
    while (i != 0 && line[i] != ';')
    {
        if (line[i] == '>' || line[i] == '<' || ft_isalnum(line[i]) == 1)
            return (1);
        i--;
    }
    return (0);
}
void parse_list_command(t_list_cmd *l_cmd, char *line)
{
    int i;
    int k;
    int save;
    char *s_command;
    int check;

    i = 0;
    save = 0;
    while (line[i])
    {
        k = 0;
        if (is_correct(line[i]) == 0)
        {
            ft_putstr_fd("error 1", 2);
            exit(1);
        }
        if (line[i] == ';')
        {
            s_command = alloc_command(line, i, &save);
            parse_command(l_cmd, s_command);

            free(s_command);
        }
        i++;
    }
    if (check_parse_list_command(line, i) == 1)
    {
        s_command = alloc_command(line, i, &save);
        parse_command(l_cmd, s_command);

        free(s_command);
    }
}
int main(int argc, char **argv, char **env)
{
    int fd;
    t_list_cmd *l_command;
    t_path path;
    t_key key;
    t_cmd cmd;

    l_command = NULL;
    fd = open("command.txt", O_RDWR);
    char *line;
    get_next_line(fd, &line);
    ft_check_line(line);
    if (line[0] == '\0')
        return (0);
    l_command = add_list_cmd(l_command);
    parse_list_command(l_command, line);

    printf("-------------------------------before sort-------------------------------\n");
    print(l_command);
    sort(l_command);
    printf("-------------------------------after sort-------------------------------\n");
    print(l_command);
    init(&path, &key, &cmd);
    path.env->fullenv = env;
    return (0);
}
// i = check(line, &test);
// printf("|i==> %d|\t|\t %s \t|\n", i, test);
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);