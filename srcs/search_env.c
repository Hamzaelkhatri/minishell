/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:16:07 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/16 13:56:54 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *search_env(char **env,char *str)
{
    int i;
    int j;
    char *tmp;

    j = ft_strlen(str)+1;
    i = 0;
    while (env[i])
    {
        if (ft_strnstr(env[i],str,ft_strlen(env[i])))
        {
            tmp = ft_strnstr(env[i],str,ft_strlen(env[i]));
            return &tmp[j];
        }
        i++;
    }
    return (NULL);
}