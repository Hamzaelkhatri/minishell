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

// void alloc_affect(t_list_cmd *l_cmd, char *command, int indice)
// {

//     if (indice == 1)
//     {
//         l_cmd->command->tool.cmd = 1;
//         l_cmd->command = add_simple_cmd(l_cmd->command, 1);
//         if (l_cmd->command->s_left->right != NULL)
//             l_cmd->command->s_left = l_cmd->command->s_left->right;
//         l_cmd->command->s_left->l_element->cmd = ft_strdup(command);
//     }
//     else if (indice == 2)
//     {
//         l_cmd->command->tool.argument = 2;
//         l_cmd->command = add_simple_cmd(l_cmd->command, 2);
//         if (l_cmd->command->s_left->right != NULL)
//             l_cmd->command->s_left = l_cmd->command->s_left->right;
//         l_cmd->command->s_left->l_element->argument = ft_strdup(command);
//     }
//     else if (indice == 3)
//     {
//         l_cmd->command->tool.argument = 3;
//         l_cmd->command = add_simple_cmd(l_cmd->command, 3);
//         if (l_cmd->command->s_left->right != NULL)
//             l_cmd->command->s_left = l_cmd->command->s_left->right;
//         l_cmd->command->s_left->l_element->redirection.file = ft_strdup(command);
//         if (wich_redirection(l_cmd->command->tool.check_io) == 2)
//             l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup(">>");
//         else if (wich_redirection(l_cmd->command->tool.check_io) == 1)
//             l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup(">");
//         else if (wich_redirection(l_cmd->command->tool.check_io) == 3)
//             l_cmd->command->s_left->l_element->redirection.i_o = ft_strdup("<");
//     }
// }

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


// void parcs_this_simple_command(char *s_command, t_list_cmd *l_cmd, char separator, int y_or_n)
// {
//     t_command *tmp_command;
//     int i = 0;
//     tmp_command = l_cmd->command;
//     if (l_cmd->command->s_left->l_element != NULL)
//         l_cmd->command = add_command(l_cmd->command);
//     while (l_cmd->command->right != NULL)
//         l_cmd->command = l_cmd->command->right;
//     ft_bzero(&l_cmd->command->tool, sizeof(t_tool));
//     l_cmd->command->tool.tab = ft_space_split_quote(s_command);
//     check_element(l_cmd);
//     l_cmd->command = tmp_command;
// }




int check_parse_list_command(char *line, int i)
{
    while ((i != 0 && ft_isalnum(line[0]) != 1) || line[i] != ';')
    {

        if (line[i] == '>' || line[i] == '<' || ft_isalnum(line[i]) == 1)
            return (1);
        i--;
    }
    return (0);
}


void free_scommand(t_simple_command **scommand)
{
    if (*scommand != NULL)
        free_scommand(&(*scommand)->right);
    if (*scommand != NULL)
        free_s_command(&(*scommand));
}

void free_command(t_command **command)
{
    if (*command != NULL)
        free_command(&(*command)->right);
    if (*command != NULL)
    {
        free_scommand(&(*command)->s_left);
        if ((*command)->tool.tab != NULL)
            free_tab(&(*command)->tool.tab);
        free(*command);
        *command = NULL;
    }
}
void free_lcommand(t_list_cmd **l_command)
{
    if (*l_command != NULL)
        free_lcommand(&(*l_command)->next);
    if (*l_command != NULL)
    {
        free_command(&(*l_command)->command);
        free(*l_command);
        *l_command = NULL;
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
    sort(l_command);
    quotes(l_command);
    // check_scommand(l_command);
    init(&path, &key, &cmd);
    path.env->fullenv = env;
    // print_working_directory(&path);
    // unset_cmd("PWssssD",&path);
    // show_env(path.env->fullenv);
    // cd_cmd("../../..",&path);
    // getprogramme(&path,"");
    // printf("%s",);
    // if(cmdcheck(l_command->command->s_left->l_element->cmd))
    //     get_cmd(l_command->command->s_left->l_element->cmd,&path,l_command->command);
    // else
    //     execute_foreign(l_command,0);
    
    commande_effect(l_command,&path);
    // print_working_directory(&path);
    // pipes_cmd(&path, l_command);
    // export_cmd("hello=shihaja",path.env->fullenv);
    // show_env(path.env->fullenv);
    return (0);
}