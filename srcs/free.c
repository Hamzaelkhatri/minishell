#include "minishell.h"

void free_tab(char ***tab)
{
    int index;

    index = 0;
    if (*tab != NULL && *tab[index] != NULL)
    {
        while ((*tab)[index])
        {
            free((*tab)[index]);
            (*tab)[index] = NULL;
            index++;
        }
        free(*tab);
        *tab = NULL;
    }
}

void free_element(t_elements **element)
{
    if ((*element)->cmd != NULL)
    {
        free((*element)->cmd);
        (*element)->cmd = NULL;
    }
    if ((*element)->argument != NULL)
    {
        free((*element)->argument);
        (*element)->argument = NULL;
    }
    if ((*element)->redirection.file != NULL)
    {
        free((*element)->redirection.file);
        free((*element)->redirection.i_o);
        (*element)->redirection.file = NULL;
        (*element)->redirection.i_o = NULL;
    }
    if (*element != NULL)
    {
        free(*element);
        *element = NULL;
    }
}
void free_s_command(t_simple_command **s_command)
{
    free_element(&(*s_command)->l_element);
    free(*s_command);
    *s_command = NULL;
}
void free_line(char *line)
{
    free(line);
    line = NULL;
}

void free_scommand(t_simple_command **scommand)
{
    if (*scommand != NULL)
        free_scommand(&(*scommand)->right);
    if (*scommand != NULL)
        free_s_command(&(*scommand));
}

void free_command(t_command **command)
{
    if (*command != NULL)
        free_command(&(*command)->right);
    if (*command != NULL)
    {
        free_scommand(&(*command)->s_left);
        if ((*command)->tool.tab != NULL)
            free_tab(&(*command)->tool.tab);
        free(*command);
        *command = NULL;
    }
}
void free_lcommand(t_list_cmd **l_command)
{
    if (*l_command != NULL)
        free_lcommand(&(*l_command)->next);
    if (*l_command != NULL)
    {
        free_command(&(*l_command)->command);
        free(*l_command);
        *l_command = NULL;
    }
}

void ft_strdel(char **as)
{
    if (as != NULL)
    {
        free(*as);
        *as = NULL;
    }
}