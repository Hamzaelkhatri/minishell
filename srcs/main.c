#include "minishell.h"

int check_what_after(char c)
{
    if (c != '/' && c != '\\' && c != '|' && c != '~' && c != '\n' && ft_isprint(c) == 1)
        return (1);
    return (0);
}

int check_redirection(char *line, int *i)
{

    if (line[*i] == '>' && line[*i + 1] == '>')
    {
        (*i)++;
        if (line[*i + 1] == '\0')
            return (*i == 0) ? (5) : (6);
        else if (check_what_after(line[*i + 1]) == 1)
            return (*i == 0) ? (7) : (8);
    }
    else if (line[*i] == '>')
    {
        if (line[*i + 1] == '\0')
            return (*i == 0) ? (1) : (2);
        else if (check_what_after(line[*i + 1]) == 1)
            return (*i == 0) ? (3) : (4);
    }
    else if (line[*i] == '<')
    {
        if (line[*i + 1] == '\0')
            return (*i == 0) ? (9) : (10);
        else if (check_what_after(line[*i + 1]) == 1)
            return (*i == 0) ? (11) : (12);
    }
    return (0);
}

int check_io_redirection(char *line, int *p, int *check_o_i)
{
    int redirection;

    redirection = check_redirection(line, p);
    // printf("%s\n", &line[*p]);
    *check_o_i = redirection;
    if (p == 0 && redirection > 0) // redirection hiya lawla
        return (1);
    else if (redirection > 0) // kayna shi haja 9bal redirection
        return (2);
    else
        return (0); //  kayna shi erreur
}

int check_type_element(char *line, int *check_i_o, int count)
{
    int i;
    int redirection;

    i = 0;
    redirection = -1;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
            redirection = check_io_redirection(line, &i, check_i_o);
        i++;
    }
    if (redirection == 0)
    {
        ft_putstr_fd("\nerror 2\n", 2);
        exit(1);
    }
    if (count == 0 && redirection == -1)
        return (1);                                                                                     // awal indice khasso ikun commande ila la khass tretourna errour << kandon hh !>>
    else if (count == 0 && redirection == 1 && (*check_i_o == 3 || *check_i_o == 1 || *check_i_o == 5)) // '\0' && 3 >>
        return (2);                                                                                     // badya b rederction > <
    else if (count == 0 && redirection == 1 && (*check_i_o == 4 || *check_i_o == 2 || *check_i_o == 6)) //
        return (3);                                                                                     // badya b rederction
    else if (redirection == 1 && (*check_i_o == 3 || *check_i_o == 1 || *check_i_o == 5))               // '\0' 3 >>
        return (4);                                                                                     // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (redirection == 1 && (*check_i_o == 4 || *check_i_o == 2 || *check_i_o == 6))               //
        return (5);                                                                                     // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (redirection == 2 && (*check_i_o == 3 || *check_i_o == 1 || *check_i_o == 5))               // '\0' 3 >>
    {
        // printf("ya himaar\n");
        return (6);
    }                                                                                     // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (redirection == 2 && (*check_i_o == 4 || *check_i_o == 2 || *check_i_o == 6)) //
        return (7);                                                                       // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (count != 0 && redirection == -1)
        return (8);
    return (9);
}

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
void affect_redirection(char **tab, int *index, int result, int check, t_check *wich, t_list_cmd *l_cmd)
{
    char **tab_split;
    if (check == 3 || check == 4)
        l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">>");
    else if (check == 1 || check == 2)
        l_cmd->s_left->l_element->redirection.i_o = ft_strdup(">");
    else if (check == 5 || check == 6)
        l_cmd->s_left->l_element->redirection.i_o = ft_strdup("<");
    if (result == 2 || result == 4 || result == 6)
    {
        // printf("|check ==> %d|\n", check);
        if (result == 2 || (result == 4 && (tab[*index][0] == '<' || tab[*index][0] == '>')))
        {
            if (check == 3)
            {
                ft_putstr_fd("salam a sat\n", 1);
                (*index)++;
            }
            l_cmd->s_left->l_element->redirection.file = ft_strdup(tab[++(*index)]);
            // (*index)++;
        }
        else if (result == 6)
        {
            // printf("%s\n", tab[*index]);
            l_cmd->s_left->l_element->redirection.file = ft_strdup(tab[++(*index)]);
            // tab_split = input_or_output(tab[*index]);
            // l_cmd->s_left->l_element->cmd = ft_strdup(tab_split[0]);
            // ft_putstr_fd(l_cmd->s_left->l_element->cmd, 1);
        }
    }
    // else if (result ==)
}

void check_element(char **tab, t_list_cmd *l_cmd)
{
    int i;
    int check;
    int ret;
    t_redirection rdrct;
    t_check wich;

    ft_bzero(&wich, sizeof(t_check));
    i = 0;
    while (tab[i])
    {
        check = -1;
        ret = check_type_element(tab[i], &check, i);
        if (ret > 0)
            l_cmd = add_simple_cmd(l_cmd);
        if (ret == 1 || ret == 8)
        {
            if (wich.cmd == 0)
            {
                l_cmd->s_left->l_element->cmd = ft_strdup(tab[i]);
                printf("|cmd ==> %s|\n", l_cmd->s_left->l_element->cmd);
            }
            else
            {

                l_cmd->s_left->l_element->argument = ft_strdup(tab[i]);
                printf("|argument  ==> %s|\n", l_cmd->s_left->l_element->argument);
            }
            ft_wich(&wich, 1);
        }
        else if (ret >= 2 && ret <= 7)
        {
            affect_redirection(tab, &i, ret, check, &wich, l_cmd);
            printf("|direction ==> %s|\t|redirection ==> %s|\n", l_cmd->s_left->l_element->redirection.i_o, l_cmd->s_left->l_element->redirection.file);
        }
        i++;
    }
}
void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
{
    char **tab;
    t_list_cmd *tmp;

    tmp = l_cmd;
    tab = ft_space_split(s_command);

    l_cmd = add_list_cmd(l_cmd);
    // ft_bzero(l_cmd, sizeof(t_list_cmd));
    // l_cmd = add_simple_cmd(l_cmd);
    check_element(tab, l_cmd);
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