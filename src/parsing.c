/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/21 12:23:05 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//https://guide.bash.academy/commands/

void print_nested_lklist(t_list_cmd *lst, t_shell *sh)
{
    int i;

    i = 0;
    int j = 0;

    while (lst != NULL)
    {
        j = 0;
        while (lst->pipe != NULL)

        {

            printf("for node %d |==>{ %s }In list_pipe for node {%i} |==>|%s| \n", i, lst->cmd, j, lst->pipe->str_pipe);
            // printf("in node %i this cmd : %s\n",i, sh->sh_cmd);
            // printf("in node %i this is arg : %s\n",i, sh->sh_arg);

            lst->pipe = lst->pipe->next;
            j++;
        }
        lst = lst->next;

        i++;
    }
}
void ft_check_comma(char *line, t_shell *sh)
{
    int i;

    i = 0;
    sh->comma = 0;
    while (line[i])
    {
        if (line[i] == ';')
        {
            sh->comma = 1;
            sh->count_comma++;
        }
        i++;
    }
}
void ft_check_pipe(char *line, t_shell *sh)
{
    int i;

    i = 0;
    sh->pipe  = 0;
    while (line[i])
    {
        if (line[i] == '|')
        {
            sh->pipe = 1;
        }
        i++;
    }
}

void handle_line(t_shell *sh, t_read *rd, t_list_cmd *lst, char **env)
{
    t_list_cmd *new;
    t_list_cmd *tmp;
    int i;

    i = 0;
    new = NULL;
    lst = NULL;
    ft_check_comma(rd->line, sh);
    ft_check_comma(rd->line,sh);
    if (sh->pipe == 1 && sh->comma == 0)
        sh->simple_cmd = ft_split(rd->line, '|');
    if (sh->comma == 1)
        sh->simple_cmd = ft_split(rd->line, ';');
    else
        sh->simple_cmd = ft_split(rd->line, '\0');
    while (sh->simple_cmd[i] != NULL)
    {
        new = creat_node(sh->simple_cmd[i]);
        add_cmd(&lst, new);
        i++;
        new = NULL;
    }
     seperat_with_pipe(sh, lst);
    print_nested_lklist(lst, sh);
   // define_each(sh, lst, env);
}

void define_each(t_shell *sh, t_list_cmd *lst, char **env)
{
    char **tmp;
    int i;
    int j;

    i = 0;
    j = 0;
    search_all(env);
    i = 1;
    while (lst != NULL)
    {
        tmp = NULL;
        while (lst->pipe != NULL)
        {

            tmp = ft_space_split(lst->pipe->str_pipe);
            sh->sh_cmd = tmp[0];
            sh->sh_arg = tmp[1];
            lst->pipe = lst->pipe->next;
        } // i++;
        lst = lst->next;
    }
}