/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:28:46 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/20 19:01:46 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd  *creat_node(char *content)
{
    t_list_cmd *lst;
    lst = malloc(sizeof(t_list_cmd));
    lst->cmd = content;
    lst->next = NULL;
    return(lst);
}

void add_cmd(t_list_cmd **head, t_list_cmd *new_cmd)
{
    t_list_cmd *new;

    if (!head || !new_cmd)
        return;
    new = *head;
    if (new)
    {
        while (new->next)
            new = new->next;
        new->next = new_cmd;
    }
    else 
        *head = new_cmd;
}
t_pipe *creat_node_p(char *content)
{
    t_pipe *lst;
    lst = malloc(sizeof(t_pipe));
    lst->str_pipe = content;
    lst->next = NULL;
    return (lst);
}

void add_pipe_list(t_pipe **head, t_pipe *new_cmd)
{
    t_pipe *new;

    if (!head || !new_cmd)
        return;
    new = *head;
    if (new)
    {
        while (new->next)
            new = new->next;
        new->next = new_cmd;
    }
    else
        *head = new_cmd;
}