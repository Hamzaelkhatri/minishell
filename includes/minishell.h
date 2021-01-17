#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "get_next_line.h"

typedef struct s_key
{
    int cntrd;
} t_key;

typedef struct s_env
{
    char **fullenv;
    char *pwd;
    char *oldpwd;
} t_env;

typedef struct s_path
{
    char *path;
    // char **env;
    t_key *key;
    char *cmds;
    char *pathcmd;
    t_env *env;
    char *p;
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
} t_cmd;



// modiffit les structures !!!!!!!!!!!!!!!
typedef struct s_redirection
{
    char *i_o;
    char *file;
} t_redirection;

typedef struct s_check
{
    int cmd;
    int word;
    int redirection;
} t_check;

typedef struct s_tool
{
    char **tab;
    int i;
    int result;
    int check_io;
    int indice;
    int cmd;
    int argument;
    int redirection;
} t_tool;

typedef struct s_elements
{
    int indice;
    char *cmd;
    char *argument;
    t_redirection redirection;
} t_elements;

typedef struct s_simple_command
{
    t_elements *l_element;
    struct s_simple_command *parent;
    struct s_simple_command *right;
} t_simple_command;


typedef struct s_command
{
    t_tool tool;
    t_simple_command *s_left;
    struct s_command *right;
} t_command;

typedef struct s_list_cmd
{
    t_command *command;
    char *line;
    struct s_list_cmd *next;
    struct s_list_cmd *previous;
} t_list_cmd;

typedef struct s_tmp
{
    t_list_cmd *lc;
    t_command *command;
    t_simple_command *sc;
    t_simple_command *cmd;
} t_tmp;


void ft_putchar(char c);
void ft_putstr(char *str);
char **ft_space_split(char const *s);
int check(char *line, char **test);
int is_correct(char c);
void ft_wich(t_check *wich, int number);
char **ft_space_split(char const *s);
char **ft_space_split_quote(char const *s);

// allocation

t_list_cmd *add_list_cmd(t_list_cmd *parent);
t_command *add_command(t_command *parent, t_list_cmd *l_cmd);
t_command *add_simple_cmd(t_command *parent, int i, t_list_cmd *l_cmd);
void alloc_affect(t_list_cmd *l_cmd, char *command, int indice);

// check

void ft_check_line(char *line);
int check_type_element(char *line, int *check_i_o, int count);
int check_io_redirection(char *line, int *p, int *check_o_i);
void check_element(t_list_cmd *l_cmd);
int check_what_after(char c);

// redirection_tools

void affect_redirection(t_list_cmd *l_cmd);
int wich_redirection(int check);
int check_io_redirection(char *line, int *p, int *check_o_i);
int check_redirection(char *line, int *i);

// sort

void sort(t_list_cmd *l_cmd);

// print
void print(t_list_cmd *l_command);

// s_command

void check_scommand(t_list_cmd *l_cmd);

// tools
char *ignoring_quote(char *line);
void quotes(t_list_cmd *l_cmd);
char *ft_strjoin_command(t_simple_command *cmd);

// parse

void parcs_simple_command(char *s_command, t_list_cmd *l_cmd);
void parse_command(t_list_cmd *l_cmd, char *line);
void parse_list_command(t_list_cmd *l_cmd, char *line);

// free
void free_tab(char ***tab);
void ft_strdel(char **as);
void free_element(t_elements **element);
void free_s_command(t_simple_command **s_command);
void free_scommand(t_simple_command **scommand);
void free_command(t_command **command);
void free_lcommand(t_list_cmd **l_command);
void ft_exit(t_list_cmd *l_cmd, int error);

// init
void init_simple_cmd(t_simple_command **parent, int i);
void init_lcommand(t_list_cmd **parent);
//
void loop_shell(t_path *path);
void init(t_path *path, t_key *key, t_cmd *cmd);
void show_env(char **path);
char *search_env(char **env, char *str);
void print_working_directory(t_path *path);
void exeute(t_path *path, char *cmd);
char **ft_split_quotes(char const *s, char c);
char **ft_space_split(char const *s);
char *ft_str_in_str(const char *s1, const char *s2);
int ft_2strlen(char **str);
void get_directory(t_path *path);
int check_path(char *path, char *cmd);
void getprogramme(t_path *path, char *cmd);
char **ft_split_whitespaces(char *str);
void shift(int fd);
void shift_extra(char *file, char *shifts);
char *get_var_env(t_path *path, char *var);
void cd_cmd(char *nextpath, t_path *path);
int count_line(char **env);
void export_cmd(char *name, char **env);
void unset_cmd(char *name, t_path *path);
int search_str(char *str1, char *str2, int l1, int l2);
char *ft_str_to_equal(const char *s1, const char *s2, int len);
void    pipes_cmd(t_path * path, t_list_cmd *lst);
void ft_sortstr(char **str);
char **ft_strdup_extra(char **str);
int     cmdcheck(char *str);
int cout_to_char(char *str,char c);
void edit_env(char **env,char *var,char *res);
void execute_foreign(t_list_cmd *lst,int piping);
int lstsize(t_list_cmd *lst);
int commande_effect(t_list_cmd *lst,t_path *path);
int get_cmd(char *cmd,t_path *path,t_command *l_cmd);
int get_cmd_(char *cmd,t_path *path,t_command *l_cmd);
void free_lcommand(t_list_cmd **l_command);
void bash_promp();
#endif
