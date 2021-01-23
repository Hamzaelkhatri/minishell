/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:56:11 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 15:30:09 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cd_cmd(char *nextPath, t_path *path)
{
    char *s;
    if (!nextPath)
    {
        nextPath = get_var_env(path, "$HOME");
        if (chdir(nextPath) < 0)
        {
            ft_putendl_fd(strerror(errno), 1);
        }
    }
    nextPath = ft_strtrim(nextPath," ");
    if (!nextPath || !ft_strcmp(nextPath, "~"))
    { 
        nextPath = get_var_env(path, "$HOME");
        if (chdir(nextPath) < 0)
        {
            ft_putendl_fd(strerror(errno), 1);
        }
    }
    else if (nextPath[0] == '$')
    {
        s = get_var_env(path, nextPath);
        if (!s && (chdir(nextPath) < 0))
            ft_putendl_fd(strerror(errno), 1);
        else
        {
            nextPath = get_var_env(path, nextPath);
            if (chdir(nextPath) < 0)
            {
                ft_putendl_fd(strerror(errno), 1);
            }
        }
    }
    else if (chdir(nextPath) < 0)
    {
        ft_putstr_fd(nextPath,1);
        ft_putendl_fd(strerror(errno), 1);
    }
}