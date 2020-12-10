/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:34:46 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/10 14:45:55 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include  <signal.h>
# include  <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
#include <sys/types.h>
#include <dirent.h>
# define BUFFER_SIZE 1024

typedef struct s_key
{
    int     cntrd;
}t_key;

typedef struct s_env
{
    char **fullenv;
    char *pwd;
    char *oldpwd;
}t_env;

typedef struct s_path
{
    char *path;
    // char **env;
    t_key *key;
    char *cmds;
    char *pathcmd;
    t_env *env;
} t_path;




typedef struct s_cmd
{
    int echo;
    int pwd;
    int exit;
    int env;
    int export;
    int unset;
    int cd;
}t_cmd;

typedef struct s_token
{
	char *token;
	struct s_token *next;
}t_token;

void    loop_shell(t_cmd *cmd,t_path *path);
void    init(t_path *path,t_key *key,t_cmd *cmd);
void    show_env(char **path);
char    *search_env(char **env,char *str);
void	print_working_directory(t_path *path);
void    exeute(t_path *path,char *cmd);
char    **ft_space_split(char const *s);
char    *ft_str_in_str(const char *s1, const char *s2);
int     ft_2strlen(char **str);
void    get_directory(t_path *path);
int     check_path(char *path,char *cmd);
void    getprogramme(t_path *path,char *cmd);
t_token *ft_parse(char *line);
char    **ft_split_whitespaces(char *str);
void    cd_cmd(char *nextpath,t_path *path);

#endif
