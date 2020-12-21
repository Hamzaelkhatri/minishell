/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:30:13 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/21 12:19:30 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sh_initial(t_shell *sh, t_list_cmd *lst)
{
    sh->pipe = 0;
    sh->comma = 0;
    sh->count_pipe = 0;
    sh->count_comma = 0;
    ft_bzero(lst, sizeof(t_list_cmd));
}

void check_line_error(char *line)
{
    int i;
    char **sp_free;

    i = 0;
    sp_free = ft_space_split(line);
    //        while ( sp_free[i])
    // {
    //     printf("==>%s\n",sp_free[i]);
    //     i++;
    // }
    while (line[i] != '\0')
    {
        // printf("==>%s\n",line);
        if ((line[i] == '|' && line[i + 1] == ';') || (line[i] == ';' && line[i + 1] == '|'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == ';' && line[i + 1] == ';'))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (sp_free[i] != (void *)0)
    {
        if ((ft_strcmp(sp_free[i], "|") == 0 && ft_strcmp(sp_free[i + 1], ";") == 0) || (ft_strcmp(sp_free[i], ";") == 0 && ft_strcmp(sp_free[i + 1], "|") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        if ((ft_strcmp(sp_free[i], "|") == 0 && ft_strcmp(sp_free[i + 1], "|") == 0) || (ft_strcmp(sp_free[i], ";") == 0 && ft_strcmp(sp_free[i + 1], ";") == 0))
        {
            printf("Error : Syntax error\n");
            exit(1);
        }
        i++;
    }
}

int main(int argc, char **argv, char **env)
{
    t_read rd;
    t_shell sh;
    t_list_cmd lst;
    int i;

    i = 0;
    (void)argc;
    rd.fd = open("cmd.txt", O_RDONLY);
    rd.line = malloc(sizeof(char) * BUFFER_SIZE);
    read(rd.fd, rd.line, BUFFER_SIZE);
    // while ( env[i]!= NULL)
    // {

    //     printf("for node %d |==>{%s}\n",i,env[i]);
    //     i++;
    // }
    sh_initial(&sh, &lst);
    check_line_error(rd.line);
    handle_line(&sh, &rd, &lst, env);
}