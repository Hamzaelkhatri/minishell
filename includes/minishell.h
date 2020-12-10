#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

typedef struct s_sc_element
{
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
    char separator;
    t_simple_command s_command;
    struct s_list_cmd *next;
} t_list_cmd;
void ft_putchar(char c);
void ft_putstr(char *str);
char **ft_space_split(char const *s);

#endif