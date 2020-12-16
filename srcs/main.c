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

// void chi_haja(t_list_cmd *l_cmd, char *command, int indice)
// {
//     if (indice == 1)
//     {
//         l_cmd = add_simple_cmd(l_cmd, 1);
//         l_cmd->s_left->l_element->cmd = ft_strdup(command);
//     }
//     else if (indice == 2)
//     {
//         l_cmd = add_simple_cmd(l_cmd, 2);
//         // while (l_cmd->s_left->right != NULL)
//         //     l_cmd->s_left = l_cmd->s_left->right;
//         l_cmd->s_left->l_element->argument = ft_strdup(command);
//     }
//     else if (indice == 3)
//     {
//     }
// }
// void affect_redirection(char **tab, int *index, int result, int check, t_check *wich, t_list_cmd *l_cmd)

void affect_redirection(t_tool *tool, t_list_cmd *l_cmd)
{
    char **tab_split;

    if (tool->result == 3 || tool->result == 4 || tool->result == 5)
    {
        if (tool->check_io == 1 || tool->check_io == 2 || tool->check_io == 3 || tool->check_io == 4 || tool->check_io == 5 || tool->check_io == 6 || tool->check_io == 7 || tool->check_io == 8)
            tab_split = ft_split(tool->tab[tool->i], '>');
        else
            tab_split = ft_split(tool->tab[tool->i], '<');
        if (tool->result == 3)
        {
            l_cmd = add_simple_cmd(l_cmd, 3);
            l_cmd->s_left->l_element->redirection.file = ft_strdup(tab_split[0]);
        }
        else if (tool->result == 4 || tool->result == 5)
        {
            if (tool->wich.cmd == 0)
            {
                l_cmd = add_simple_cmd(l_cmd, 1);
                l_cmd->s_left->l_element->cmd = ft_strdup(tab_split[0]);
            }
            else
            {
                l_cmd = add_simple_cmd(l_cmd, 2);
                l_cmd->s_left->l_element->argument = ft_strdup(tab_split[0]);
            }
            if (tool->result == 4)
            {
                l_cmd = add_simple_cmd(l_cmd, 3);
                l_cmd->s_left->l_element->redirection.file = ft_strdup(tool->tab[++tool->i]);
                ft_wich(&tool->wich, 1);
            }
            else if (tool->result == 5)
            {
                l_cmd = add_simple_cmd(l_cmd, 3);
                l_cmd->s_left->l_element->redirection.file = ft_strdup(tab_split[1]);
                ft_wich(&tool->wich, 1);
            }
        }
    }
    if (tool->result == 2)
    {
        l_cmd = add_simple_cmd(l_cmd, 3);
        l_cmd->s_left->l_element->redirection.file = ft_strdup(tool->tab[++tool->i]);
    }
    if (tool->check_io == 5 || tool->check_io == 6 || tool->check_io == 7 || tool->check_io == 8)
        l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">>");
    else if (tool->check_io == 1 || tool->check_io == 2 || tool->check_io == 3 || tool->check_io == 4)
        l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">");
    else if (tool->check_io == 9 || tool->check_io == 10 || tool->check_io == 11 || tool->check_io == 12)
        l_cmd->s_left->l_element->redirection.i_o = ft_strdup("<");
    l_cmd->s_left = l_cmd->s_left->right;
}

void check_element(t_tool *tool, t_list_cmd *l_cmd)
{
    int check;
    t_simple_command *tmp;
    ft_bzero(&tool->wich, sizeof(t_check));
    tool->i = 0;
    tmp = l_cmd->s_left;
    while (tool->tab[tool->i])
    {

        tool->check_io = -1;
        tool->result = check_type_element(tool->tab[tool->i], &tool->check_io, tool->i);
        if (tool->result == 1 || tool->result == 6)
        {
            if (tool->wich.cmd == 0)
            {
                l_cmd = add_simple_cmd(l_cmd, 1);
                l_cmd->s_left->l_element->cmd = ft_strdup(tool->tab[tool->i]);
            }
            else
            {
                l_cmd = add_simple_cmd(l_cmd, 2);
                while (l_cmd->s_left->right != NULL)
                    l_cmd->s_left = l_cmd->s_left->right;
                l_cmd->s_left->l_element->argument = ft_strdup(tool->tab[tool->i]);
            }
            ft_wich(&tool->wich, 1);
        }
        // else if (tool->result >= 2 && tool->result <= 5)
        // {
        //     affect_redirection(tool, l_cmd);
        //     // printf("|direction ==> %s|\t|redirection ==> %s|\n", l_cmd->s_left->l_element->redirection.i_o, l_cmd->s_left->l_element->redirection.file);
        // }
        tool->i++;
    }
    // if (tmp == NULL)
    l_cmd->s_left = tmp;
    // ft_putstr_fd("ha wahad salam 3alaykum \n", 1);
}

void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    t_tool tool;
    t_list_cmd *tmp;

    ft_bzero(&tool, sizeof(t_tool));
    tmp = l_cmd;
    tool.tab = ft_space_split(s_command);
    // l_cmd = add_list_cmd(l_cmd);
    check_element(&tool, l_cmd);
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
    ft_check_line(line);
    l_command = add_list_cmd(l_command);
    parcs(line, l_command);
    if (l_command->s_left->l_element == NULL)
        ft_putstr_fd("minirt\n", 1);
    ft_putstr("sahbi anouar wa3ar\n");
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
    return (0);
}
// i = check(line, &test);
// printf("|i==> %d|\t|\t %s \t|\n", i, test);
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);