#include "minishell.h"

int			wich_redirection(int check)
{
	if (check == 5 || check == 6 || check == 7 || check == 8)
		return (2);
	else if (check == 1 || check == 2 || check == 3 || check == 4)
		return (1);
	else if (check == 9 || check == 10 || check == 11 || check == 12)
		return (3);
	return (0);
}

int			check_io_redirection(char *line, int *p, int *check_o_i)
{
	int redirection;

	redirection = check_redirection(line, p);
	if (redirection == 5 || redirection == 7 ||
			redirection == 8 || redirection == 6)
		(*p)++;
	*check_o_i = redirection;
	if (redirection > 0)
		return (1);
	else
		return (0);
}

int			check_redirection(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		if (line[*i + 2] == '\0')
			return (*i == 0) ? (5) : (6);
		else if (check_what_after(line[*i + 2]) == 1)
			return (*i == 0) ? (7) : (8);
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '\0')
			return (*i == 0) ? (1) : (2);
		else if (check_what_after(line[*i + 1]) == 1)
			return (*i == 0) ? (3) : (4);
	}
	else if (line[*i] == '<' && line[*i + 1] != '<')
	{
		if (line[*i + 1] == '\0')
			return (*i == 0) ? (9) : (10);
		else if (check_what_after(line[*i + 1]) == 1)
			return (*i == 0) ? (11) : (12);
	}
	return (0);
}

static void	affect_redirection_ex(t_list_cmd *l_cmd,
		int result, char ***tab_split)
{
	if (wich_redirection(l_cmd->command->tool.check_io) == 2\
			|| wich_redirection(l_cmd->command->tool.check_io) == 1)
		*tab_split = ft_split(l_cmd->command->tool.tab[l_cmd->command->tool.i]\
			, '>');
	else
		*tab_split = ft_split(l_cmd->command->tool.tab[l_cmd->command->tool.i]\
			, '<');
	if (result == 3)
		alloc_affect(l_cmd, (*tab_split)[0], 3);
	else if (result == 4 || result == 5)
	{
		if (l_cmd->command->tool.cmd == 0)
			alloc_affect(l_cmd, (*tab_split)[0], 1);
		else
			alloc_affect(l_cmd, (*tab_split)[0], 2);
		if (result == 4)
			alloc_affect(l_cmd,\
				l_cmd->command->tool.tab[++l_cmd->command->tool.i], 3);
		else if (result == 5)
			alloc_affect(l_cmd, (*tab_split)[1], 3);
	}
}

void		affect_redirection(t_list_cmd *l_cmd)
{
	char	**tab_split;
	int		result;

	tab_split = NULL;
	result = l_cmd->command->tool.result;
	if (result == 3 || result == 4 || result == 5)
		affect_redirection_ex(l_cmd, result, &tab_split);
	if (result == 2)
		alloc_affect(l_cmd,\
			l_cmd->command->tool.tab[++l_cmd->command->tool.i], 3);
	if (tab_split != NULL)
		free_tab(&tab_split);
}
