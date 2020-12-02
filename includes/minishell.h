/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:34:46 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/01 19:11:02 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include  <signal.h>
# include  <stdio.h>
#include    <string.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 1024

typedef struct s_path
{
    char *path;
    char **env;
} t_path;

void    loop_shell(void);
void    init(t_path *path);
void    show_env(char **path);
char    *search_env(char **env,char *str);
void	print_working_directory(char** env);
#endif
