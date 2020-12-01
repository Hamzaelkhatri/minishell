/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:34:46 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/01 12:23:24 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include  <signal.h>
# include  <stdio.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 1024

typedef struct s_path
{
    char *path;
    char **env;
} t_path;

typedef struct	s_token
{
	char			*tk_value;
	struct s_token 	*next;
}				t_token;

void    		loop_shell(void);
void    		init(t_path *path);
void    		show_env(char **path);
char    		*search_env(char **env,char *str);
void			print_working_directory(char** env);
void			ft_echo(char  *str,int option);
t_token			*ft_parse(char *line);

#endif
