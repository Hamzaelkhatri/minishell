#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../libft/libft.h"
#include "get_next_line.h"

typedef struct s_redirection
{
    char i_o;
    char *word;
} t_redirection;

typedef struct s_check
{
    int cmd;
    int word;
    int assignement;
    int redirection;
} t_check;

typedef struct s_sc_element
{
    char *cmd;
    char *word;
    char **assignement;
    char **redirection;
} t_sc_element;

typedef struct s_simple_command
{
    t_sc_element element;
    struct s_simple_command *parent;
    struct s_simple_command *left;
} t_simple_command;

typedef struct s_list_cmd
{
    t_simple_command *s_command;
    char separator;
    struct s_list_cmd *next;
} t_list_cmd;

void ft_putchar(char c);
void ft_putstr(char *str);
char **ft_space_split(char const *s);
int check(char *line, char **test);
int is_correct(char c);

#endif