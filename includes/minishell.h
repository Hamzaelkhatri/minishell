#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include  <signal.h>
# include  <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include<fcntl.h> 
#include<sys/wait.h>
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
    char  *p;
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
void    shift(int fd);
void    shift_extra(char *file,char *shifts);
char*	get_var_env(t_path *path,char *var);
void	cd_cmd(char *nextpath,t_path *path);
int	count_line(char **env);
void	export_cmd(char *name,char **env);
void	unset_cmd(char *name, t_path *path);
int	search_str(char *str1, char *str2, int l1, int l2);
char    *ft_str_to_equal(const char *s1, const char *s2,int len);
void    pipes_cmd(char *left, char *right, t_path * path);
void	ft_sortstr(char **str);
char **ft_strdup_extra(char **str);
#endif
