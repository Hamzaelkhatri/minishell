/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:55:08 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/13 19:53:34 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *read_line(char *line)
{
    char *buffer;
    int rd;
    int i;
    
    i = 0;
    if(!(line = malloc(sizeof(char)*BUFFER_SIZE)))
      printf("Error: %s\n", strerror(errno));
    if ( (rd = read (0,line,BUFFER_SIZE)) > 0)
    {
        if( ft_strncmp(line,"exit",4) == 0)
            exit(1);
        if (ft_strncmp(line,"\n",1) == 0 )
            line[i] = '\0';
    }
    return(line);
}