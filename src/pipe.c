/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:48:56 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/21 12:22:41 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void seperat_with_pipe(t_shell *sh, t_list_cmd *lst)
{
    int i;
    t_pipe *new;
    char **tmp;

    tmp = NULL;
    new = NULL;
    lst->pipe = NULL;
    while (lst != NULL)
    {
       ft_check_pipe(lst->cmd, sh);
    printf("for %s the sh->pipe = %d\n",lst->cmd,sh->pipe);
        if (sh->pipe == 1)
        {
            i = 0;
            tmp = ft_split(lst->cmd, '|');
            while (tmp[i] != NULL)
            {
                tmp[i] = ft_strtrim(tmp[i]," ");
                new = creat_node_p(tmp[i]);
                add_pipe_list(&(lst->pipe), new);
                new = NULL;

                i++;
            }
        }
        lst = lst->next;
    }
}