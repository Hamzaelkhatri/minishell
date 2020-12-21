/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:34:46 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/21 12:18:56 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#define BUFFER_SIZE 4096

typedef struct s_read
{
    char *line;
    int fd;
} t_read;

typedef struct s_shell
{
    int pipe;
    int comma;
    int count_pipe;
    int count_comma;
    char **simple_cmd;
    char *sh_cmd;
    char *sh_arg;
    char *sh_direct;
} t_shell;

typedef struct s_pipe
{
    char *str_pipe;
    struct s_pipe *next;
} t_pipe;

typedef struct s_list_cmd
{
    char *cmd;
    t_pipe *pipe;
    struct s_list_cmd *next;
} t_list_cmd;

void loop_sh(void);
char *read_line(char *line);
void lanch_cmd(char *line);

char **ft_space_split(char const *s);
void handle_line(t_shell *sh, t_read *rd, t_list_cmd *lst, char **env);
char **ft_char_split(char const *s, char *set);
int ft_strcmp(const char *s1, const char *s2);
void add_cmd(t_list_cmd **head, t_list_cmd *new_obj);
t_list_cmd *creat_node(char *content);
void define_each(t_shell *sh, t_list_cmd *lst, char **env);
void search_all(char **env);
int ft_strcmp(const char *s1, const char *s2);
void seperat_with_pipe(t_shell *sh, t_list_cmd *lst);
void add_pipe_list(t_pipe **head, t_pipe *new_cmd);
void ft_check_seperator(char *line, t_shell *sh);
t_pipe *creat_node_p(char *content);
void ft_check_pipe(char *line, t_shell *sh);
// void    loop_shell(t_cmd *cmd,t_path *path);
// void    init(t_path *path,t_key *key,t_cmd *cmd);
// void    show_env(char **path);
// char    *search_env(char **env,char *str);
// void	print_working_directory(t_path *path);
// void    exeute(t_path *path,char *cmd);
// char    **ft_space_split(char const *s);
// char    *ft_str_in_str(const char *s1, const char *s2);
// int     ft_2strlen(char **str);
// void    get_directory(t_path *path);
// int     check_path(char *path,char *cmd);
// void    getprogramme(t_path *path,char *cmd);
// t_token *ft_parse(char *line);
// char    **ft_split_whitespaces(char *str);
// void    cd_cmd(char *nextpath,t_path *path);

#endif
