/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:16:26 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/01 19:56:44 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error()
{
    write(1,"error",5);
    exit(1);
}

char *my_read()
{  
    int *buff;
    char *line;
    ssize_t size;

    if (read(0,buff,1040) == -1)
        return(0);
    size = read(0,buff,1040);
    if (!(line = malloc(sizeof(size))))
        error();
    return(line);
}

int main(int ac ,char *av[],char **env)
{
    int i;
    int j;
    char *line;
    long size;
    char *buf;
    char *ptr;

    i = 0;
    size = size = pathconf(".", _PC_PATH_MAX);
    // if ((buf = (char *)malloc((size_t)size)) != NULL)
    //         ptr = getcwd(buf, (size_t)size);
    // while (i < 2)
    //   {
    //       write(1,"bash-$",6);
    //     printf("=>%s\n",ptr);
        
    //         i++;
    //   }
    print_working_directory(env);
    // error();
}   