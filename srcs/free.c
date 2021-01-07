#include "minishell.h"

void	ft_strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}

void	free_tab(char ***tab)
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

void	free_element(t_elements **element)
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

void	free_s_command(t_simple_command **s_command)
{
	free_element(&(*s_command)->l_element);
	free(*s_command);
	*s_command = NULL;
}
