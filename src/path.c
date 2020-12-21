/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:46:33 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/17 18:32:16 by zdnaya           ###   ########.fr       */
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

int count_to_duplicate(char **str)
{
    int i = 0;
    int j = 0;
    while (str[i])
    {
        if (ft_strcmp(str[i],".") == 0) 
            j++;
        i++;
    }
    return(i - j);
}

int hide_directory(char **str,char c,int i)
{
    int j;
    int a;
    while(str[i])
    {
            if (ft_strcmp(str[i],"."))
                {
                    break;
                    return(1);
                }
        i++;
    }
    return(0);
}

void    search_all(char **env)
{
    char **str;
    char **s1;
    char *tmp;
    int i;

    i = 0;
    int j= 0;
    tmp = search_env(env,"PATH=");
        str = ft_split(tmp,':');
    j = count_to_duplicate(str) + 1;
    if(!(s1 = malloc(sizeof(char *)* j)))
        return;
    j =0;
    while (str[i])
    {
        if (hide_directory(str,'.',i) == 1)
            {
                // printf( "how many!");
                i++;
            }
        else
            {
                s1[j] = str[i];
                i++;
                j++;
            }

    }
    i =0;

    // while(s1[i])
    // {
    //     printf("==>%s\n",s1[i]);
    //     i++;
    // }
}