/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:28:24 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/16 23:30:23 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exist_or_not(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

size_t count_same_str(char const *s, char *set)
{
    int count;
    int verify;

    verify = 0;
    count = 0;
    while (*s)
    {
        if (exist_or_not(set, *s))
            verify = 0;
        else if (verify == 0)
        {
            verify = 1;
            count++;
        }
        s++;
    }
    return (count);
}

size_t count_after_same_pos(char const *s, char *set, int pos)
{
    size_t len;

    len = 0;
    while (s[pos])
    {
        if (exist_or_not(set, s[pos]) == 1)
            return (len);
        len++;
        pos++;
    }
    return (len);
}

char **ft_char_split(char const *s, char *set)
{
    char **tab;
    int i;
    int j;
    int k;

    i = -1;
    j = 0;
    k = 0;
    if (!(tab = malloc(sizeof(char *) * (count_same_str(s, set) + 1))))
        return (NULL);
    while (s[++i])
    {
        if (exist_or_not(set, s[i]) != 1)
        {
            if (k == 0)
                if (!(tab[j] = malloc(sizeof(char) * count_after_same_pos(s, set, i) + 1)))
                    return (NULL);
            tab[j][k] = s[i];
            tab[j][++k] = '\0';
        }
        if ((exist_or_not(set, s[i]) && !exist_or_not(set, s[i + 1]) && k > 0) && (k = 0) == 0)
            j++;
    }
    tab[count_same_str(s, set)] = NULL;
    return (tab);
}
