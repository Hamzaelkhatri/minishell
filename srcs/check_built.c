/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:34:39 by ahaddad           #+#    #+#             */
/*   Updated: 2020/12/25 15:18:15 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_built(t_shell *sh, t_list_cmd *lst, t_cmd *cmd)
{
    t_list_cmd *tmp;

    tmp = lst;
    
    while (lst != NULL)
    {
        if ((ft_strlen(lst->sh_cmd) == 4) && !ft_strncmp(lst->sh_cmd, "echo", 4))
        {
            cmd->echo = 1;
            printf("ila ktebte echo golha \n");
        }
        else if ((ft_strlen(lst->sh_cmd) == 2) && !ft_strncmp(lst->sh_cmd, "cd", 2))
        {
            cmd->cd = 1;
            printf("ila ktebte cd golha \n");
        }
        else if ((ft_strlen(lst->sh_cmd) == 3) && !ft_strncmp(lst->sh_cmd, "pwd", 3))
        {
              puts("here0");
            cmd->pwd = 1;
            printf("ila ktebte pwd golha \n");
        }
        else if ((ft_strlen(lst->sh_cmd) == 6) && !ft_strncmp(lst->sh_cmd, "export", 6))
        {
            cmd->export = 1;
            printf("ila export export golha \n");
        }
        else if ((ft_strlen(lst->sh_cmd) == 5) && !ft_strncmp(lst->sh_cmd, "unset", 5))
        {
            cmd->unset = 1;
            printf("ila ktebte unset golha \n");
        }
        else if ((ft_strlen(lst->sh_cmd) == 3) && !ft_strncmp(lst->sh_cmd, "env", 3))
        {
            cmd->env = 1;
            printf("ila ktebte env golha \n");
        }
        else if ((ft_strlen(lst->sh_cmd) == 4) && !ft_strncmp(lst->sh_cmd, "exit", 4))
        {
            cmd->exit = 1;
            printf("ila ktebte exit golha \n");
        }
        lst = lst->next;
    }
    lst = tmp;
}

void check_built_p(t_shell *sh, t_list_cmd *lst, t_cmd *cmd)
{
    t_list_cmd *list1;
    t_pipe *tmp1;
    
    list1 = lst;
    while (lst != NULL)
    {
        tmp1 = lst->pipe;
        while (lst->pipe != NULL)
        {
            if ((ft_strlen(lst->pipe->sh_p_cmd) == 4) && !ft_strncmp(lst->pipe->sh_p_cmd, "echo", 4))
            {
                cmd->echo = 1;
                printf("ila ktebte echo golha \n");
            }
            else if ((ft_strlen(lst->pipe->sh_p_cmd) == 2) && !ft_strncmp(lst->pipe->sh_p_cmd, "cd", 2))
            {
                cmd->cd = 1;
                printf("ila ktebte cd golha \n");
            }
            else if ((ft_strlen(lst->pipe->sh_p_cmd) == 3) && !ft_strncmp(lst->pipe->sh_p_cmd, "pwd", 3))
            {
                cmd->pwd = 1;
                printf("ila ktebte pwd golha \n");
            }
            else if ((ft_strlen(lst->pipe->sh_p_cmd) == 6) && !ft_strncmp(lst->pipe->sh_p_cmd, "export", 6))
            {
                cmd->export = 1;
                printf("ila export export golha \n");
            }
            else if ((ft_strlen(lst->pipe->sh_p_cmd) == 5) && !ft_strncmp(lst->pipe->sh_p_cmd, "unset", 5))
            {
                cmd->unset = 1;
                printf("ila ktebte unset golha \n");
            }
            else if ((ft_strlen(lst->pipe->sh_p_cmd) == 3) && !ft_strncmp(lst->pipe->sh_p_cmd, "env", 3))
            {
                cmd->env = 1;
                printf("ila ktebte env golha \n");
            }
            else if ((ft_strlen(lst->pipe->sh_p_cmd) == 4) && !ft_strncmp(lst->pipe->sh_p_cmd, "exit", 4))
            {
                cmd->exit = 1;
                printf("ila ktebte exit golha \n");
            }
            lst->pipe = lst->pipe->next;
        }
        lst->pipe = tmp1;
        lst = lst->next;
    }
    lst = list1;
}