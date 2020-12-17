#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../libft/libft.h"
#include "get_next_line.h"

// modiffit les structures !!!!!!!!!!!!!!!
typedef struct s_redirection
{
    char *i_o;
    char *file;
} t_redirection;

// typedef struct s_suffix
// {
//     t_redirection redirection;
//     char *word;
//     struct s_suffix *next;
// } t_suffix;

typedef struct s_check
{
    int cmd;
    int word;
    int redirection;
} t_check;

typedef struct s_tool
{
    char *command;
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

typedef struct s_line
{
    int pipe;
    int semicolon;
    int i_o;
} t_line;

typedef struct s_list_cmd
{
    char separator;
    t_simple_command *s_left;
    struct s_list_cmd *right;
} t_list_cmd;

void ft_putchar(char c);
void ft_putstr(char *str);
char **ft_space_split(char const *s);
int check(char *line, char **test);
int is_correct(char c);
void ft_wich(t_check *wich, int number);

// allocation

t_list_cmd *add_list_cmd(t_list_cmd *parent);
t_list_cmd *add_simple_cmd(t_list_cmd *parent, int i);

// check

void ft_check_line(char *line);
int check_type_element(char *line, int *check_i_o, int count);
int check_io_redirection(char *line, int *p, int *check_o_i);

// redirection_tools

int wich_redirection(int check);

// sort

void sort(t_list_cmd *l_cmd);

#endif