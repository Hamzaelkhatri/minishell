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

void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    t_list_cmd *tmp_lcommand;
    t_command *tmp_command;

    // ft_bzero(&tool, sizeof(t_tool));
    // tmp_lcommand = l_cmd;
    tmp_command = l_cmd->command;
    l_cmd->command->tool.tab = ft_space_split(s_command);
    if (l_cmd->command->s_left->l_element != NULL)
        l_cmd->command = add_command(l_cmd->command);
    while (l_cmd->command->right != NULL)
        l_cmd->command = l_cmd->command->right;
    check_element(l_cmd);
    l_cmd->command = tmp_command;
    // l_cmd = tmp_lcommand;
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

void parse_command(char *line, t_list_cmd *l_cmd)
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

char *alloc_command(char *line, int i, int save)
{
    char *command;
    int p;

    p = 0;
    if (!(command = (char *)malloc(sizeof(char) * (i - save))))
        return (NULL);
    while (save < i)
    {
        command[p++] = line[save++]
    }
    // khasni nmodifi hadshi man ba3d
    command[p] = '\0';
    return (command);
}
void parse_list_command(t_list_cmd *l_cmd, char *line)
{
    int i;
    int k;
    int save;
    char *s_command;

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

            s_command = (char *)malloc(sizeof(char) * (i - k));
            while (save < i)
            {
                s_command[k++] = line[save++];
            }
            s_command[k] = '\0';
            save = i + 1;
            parse_command(l_cmd, s_command);
            free(s_command);
        }
        i++;
    }
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

    printf("-------------------------------before sort-------------------------------\n");
    print(l_command->command);
    sort(l_command);
    printf("-------------------------------after sort-------------------------------\n");
    print(l_command->command);
    return (0);
}
// i = check(line, &test);
// printf("|i==> %d|\t|\t %s \t|\n", i, test);
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);