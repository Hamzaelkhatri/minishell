#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include  <signal.h>
# include  <stdio.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 1024

typedef struct s_key
{
    int     cntrd;
}t_key;

typedef struct s_path
{
    char *path;
    char **env;
    t_key *key;
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


void    loop_shell(t_cmd *cmd,t_path *path);
void    init(t_path *path,t_key *key,t_cmd *cmd);
void    show_env(char **path);
char    *search_env(char **env,char *str);
void	print_working_directory(char** env);
void    exeute(char **env);
char    **ft_space_split(char const *s);
char            *ft_str_in_str(const char *s1, const char *s2);
int             ft_2strlen(char **str);

#endif
