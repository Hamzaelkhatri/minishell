#include "minishell.h"

// t_simple_command *add_node(t_simple_command *node)
// {
//     t_simple_command *tmp;
//     t_simple_command *new;

//     tmp = node;
//     if (!(new = (t_simple_command *)malloc(sizeof(t_simple_command))))
//         return (NULL);
//     new->left = NULL;
//     new->parent = NULL;
//     if (node == NULL)
//         return (new);
//     while (tmp->left != NULL)
//     {
//         new->parent = tmp;
//         tmp = tmp->left;
//     }
//     tmp->left = new;
//     return (node);
// }

// t_simple_command *add_data(char *word)
// {
//     t_simple_command *command;
//     command = (t_simple_command *)malloc(sizeof(t_simple_command));
//     command->element.word = strdup(word);
//     return (command);
// }

// t_list_cmd *add_simple_cmd(t_list_cmd *parent)
// {
//     t_list_cmd *tmp;
//     t_list_cmd *new;
//     while (tmp->right != NULL)
//         tmp = tmp->right;
//     if (tmp->s_left == NULL)
//     {
//         if (!(tmp->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
//             return (NULL);
//         ft_bzero(tmp->s_left,sizeof(t_simple_command));
//         return(parent);
//     }
//     if(!(new = (t_list_cmd *) malloc(sizeof(t_list_cmd))))
//         return(NULL);
//     new->s_left = NULL;
//     new->right = NULL;
//     tmp->right = new;
//     return(parent);
// }

t_list_cmd *add_list_cmd(t_list_cmd *parent)
{
    t_list_cmd *tmp;
    t_list_cmd *new;

    if (parent == NULL)
    {
        if (!(parent = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
            return (NULL);
        parent->right = NULL;
        if (!(parent->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
            return (NULL);
        // ft_bzero(&parent->s_left, sizeof(t_simple_command));
        return (parent);
    }
    tmp = parent;
    if (!(new = (t_list_cmd *)malloc(sizeof(t_list_cmd))))
        return (NULL);
    new->right = NULL;
    if (!(new->s_left = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    ft_bzero(&new->s_left, sizeof(t_simple_command));
    while (tmp->right != NULL)
        tmp = tmp->right;
    tmp->right = new;
    return (parent);
}

int check_what_after(char c)
{
    if (c != '/' && c != '\\' && c != '|' && c != '~' && c != '\n' && ft_isprint(c) == 1)
        return (1);
    return (0);
}

int check_redirection(char *line, int i)
{

    // ft_putstr_fd(&line[i], 1);
    if (line[i] == '>' && line[i + 1] == '>')
    {
        if (line[i + 2] == '\0')
            return (3);
        else if (check_what_after(line[i + 2]) == 1)
            return (4);
    }
    else if (line[i] == '>')
    {
        // ft_putstr_fd("i am here\n", 1);
        if (line[i + 1] == '\0')
            return (1);
        else if (check_what_after(line[i + 1]) == 1)
            return (2);
    }
    else if (line[i] == '<' && line[i + 1] == '<')
    {
        if (line[i + 2] == '\0')
            return (7);
        else if (check_what_after(line[i + 2]) == 1)
            return (8);
    }
    else if (line[i] == '<')
    {
        if (line[i + 1] == '\0')
            return (5);
        else if (check_what_after(line[i + 1]) == 1)
            return (6);
    }
    return (0);
}

int check_io_redirection(char *line, int p, int *check)
{
    int ret;

    ret = check_redirection(line, p);

    *check = ret;
    if (p == 0 && ret > 0) // redirection hiya lawla
        return (1);
    else if (ret > 0) // kayna shi haja 9bal redirection
        return (2);
    else
        return (0); //  kayna shi erreur
}

int check_type_element(char *line, int *check, int count)
{
    int i;
    int ret;

    i = 0;
    ret = -1;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
            ret = check_io_redirection(line, i, check);
        i++;
    }
    if (ret == 0)
    {
        ft_putstr_fd("\nerror 2\n", 2);
        exit(1);
    }
    // printf("%d\n", count);
    if (count == 0 && ret == -1)
        return (1); // awal indice khasso ikun commande ila la khass tretourna errour << kandon hh !>>
    else if (count == 0 && ret == 1 && (*check == 3 || *check == 1 || *check == 5 || *check == 7))
        return (2); // badya b rederction
    else if (count == 0 && ret == 1 && (*check == 4 || *check == 2 || *check == 6 || *check == 8))
        return (3); // badya b rederction
    else if (ret == 1 && (*check == 3 || *check == 1 || *check == 5 || *check == 7))
        return (4); // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (ret == 1 && (*check == 4 || *check == 2 || *check == 6 || *check == 8))
        return (5); // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (ret == 2 && (*check == 3 || *check == 1 || *check == 5 || *check == 7))
        return (6); // mabadinsh b redirection ! o redirection mfar9a 3la li 9bal manha
    else if (ret == 2 && (*check == 4 || *check == 2 || *check == 6 || *check == 8))
        return (7); // mabadinsh b redirection ! o redirection mfar9a 3la
    else if (count != 0 && ret == -1)
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
void affect_redirection(char **tab, int *index, int result, int check, t_check *wich, t_redirection *rdrct, t_list_cmd *l_cmd)
{
    char **tab_split;
    if (check == 3 || check == 4)
        l_cmd->s_left->redirection.i_o = ft_strdup(">>");
    else if (check == 1 || check == 2)
        l_cmd->s_left->redirection.i_o = ft_strdup(">");
    else if (check == 7 || check == 8)
        l_cmd->s_left->redirection.i_o = ft_strdup("<<");
    else if (check == 5 || check == 6)
        l_cmd->s_left->redirection.i_o = ft_strdup("<");
    // printf("%d\n", result);
    if (result == 2 || result == 4 || result == 6)
    {
        if (result == 2 || (result == 4 && (tab[*index][0] == '<' || tab[*index][0] == '>')))
        {
            // ft_putstr_fd("salam a jwayn", 1);
            l_cmd->s_left->redirection.file = ft_strdup(tab[*index + 1]);
            // ft_putstr_fd(l_cmd->s_left->redirection.file, 1);
            *index++;
        }
        else if (result == 6)
        {
            tab_split = input_or_output(tab[*index]);
            l_cmd->s_left->cmd = ft_strdup(tab_split[0]);
            ft_putstr_fd(l_cmd->s_left->cmd, 1);
            // hta nzid free;
        }
    }
    // else if (result ==)
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
void check_element(char **tab, t_list_cmd *l_cmd)
{
    int i;
    int check;
    int ret;
    t_redirection rdrct;
    t_check wich;

    ft_bzero(&check, sizeof(t_check));
    ft_bzero(&wich, sizeof(t_check));
    i = 0;
    while (tab[i])
    {
        check = -1;
        ret = check_type_element(tab[i], &check, i);
        // printf("%d\n", ret);
        if (ret == 1)
        {
            l_cmd->s_left->cmd = ft_strdup(tab[i]);
            ft_wich(&wich, 1);
        }
        else if (ret >= 2 && ret <= 7)
        {
            // ft_putstr_fd("ya hala ya hala\n", 1);
            affect_redirection(tab, &i, ret, check, &wich, &rdrct, l_cmd);
        }
        // printf("%d\n", ret);
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