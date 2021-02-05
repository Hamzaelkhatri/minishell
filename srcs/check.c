#include "minishell.h"

static int	check_is_correct(char operation, char *line)
{
	int		i;
	char	c;

	i = 0;
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	c = line[i];
	if (operation == '|')
	{
		if (ft_isalnum(c) == 0 && (c == '|' || c == ';' || c == '\0'))
			return (0);
	}
	else if (operation == ';')
	{
		if ((ft_isalnum(c) == 0 && c != '\0') && (c == '|' || c == ';'))
			return (0);
	}
	else if (operation == '<')
	{
		if ((ft_isalnum(c) == 0) && (c == '\0' || c == '>' || c == '<' || c == '|' || c == ';'))
			return (0);
	}
	else if (operation == '>')
	{
		if (ft_isalnum(c) == 0 && (c == '\0' || c == '>' || c == '<' || c == '|' || c == ';'))
			return (0);
	}
	return (1);
}

static int	check_operation(char *line)
{
	if (line[0] == '|')
	{
		if (check_is_correct(line[0], &line[1]) == 0)
			return (0);
	}
	else if (line[0] == ';')
	{
		if (check_is_correct(line[0], &line[1]) == 0)
			return (0);
	}
	else if (line[0] == '>')
	{
		if (line[1] == '>')
		{
			if (check_is_correct(line[0], &line[2]) == 0)
				return (0);
		}
		else if (line[0] == '>')
			if (check_is_correct(line[0], &line[1]) == 0)
				return (0);
	}
	else if (line[0] == '<')
	{
		if (check_is_correct(line[0], &line[1]) == 0)
			return (0);
	}
	return (1);
}

static int	ft_check_line_ex(char *line, int *i)
{
	if(line[*i] == '\\')
	{
		if(count_antislach(line, *i) == 0 && line[*i + 1] == '\0')
			ft_putstr_fd("syntax error\n", 2);
		return(0);
	}

	if ((line[*i] == '|' && *i == 0) || (line[*i] == '|' &&\
		check_operation(&line[*i]) == 0))
		{
		ft_putstr_fd("syntax error\n", 2);
		return(0);
		}
	else if ((line[*i] == ';' && *i == 0) || (line[*i] == ';'\
		&& check_operation(&line[*i]) == 0))
		{
		ft_putstr_fd("syntax error\n", 2);
		return(0);
		}
	else if (line[*i] == '<' && check_operation(&line[*i]) == 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		return(0);
	}
	else if (line[*i] == '>' && check_operation(&line[*i]) == 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		return(0);
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
		(*i)++;
	return(1);
}



int		ft_check_line(char *line)
{
	int		i;
	char	quotes;
	int check = 0;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == 39) && count_antislach(line, i - 1))
		{
			quotes = line[i++];
			while (((quotes == 34 && line[i] == quotes && count_antislach(line, i - 1) == 0) || line[i] != quotes) &&  line[i])
				i++;
			if (!(line[i]))
			{
				ft_putstr_fd("syntax error\n", 2);
				return(258);
			}
		}
		else
	{
			check = ft_check_line_ex(line, &i);
			if(check == 0)
			{
				ft_putstr_fd("syntax error\n", 2);
				return(258);
			}
	}
		i++;
	}
	return(0);
}

int			check_type_element(char *line, int *check_i_o, int count)
{
	int i;
	int redirection;
	int quotes;

	i = 0;
	quotes = 0;
	redirection = -1;

	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			quotes = (quotes == 0) ? 1 : 0;
		if ((line[i] == '>' || line[i] == '<') && quotes == 0 &&  line[i - 1] != '\\')
		{
			// ft_putendl_fd("sahbi amine",1);
			return(2);
		}
		i++;
	}
	if (count == 0 && redirection == -1)
		return (1);                         
	else if (count != 0 && redirection == -1)
		return (3);
	return (0);
}


void		check_element(t_list_cmd *l_cmd)
{
	int check;

	t_simple_command *tmp;
	l_cmd->command->tool.i = 0;
	tmp = l_cmd->command->s_left;
	while (l_cmd->command->tool.tab[l_cmd->command->tool.i])
	{
		l_cmd->command->tool.check_io = -1;
		l_cmd->command->tool.result = check_type_element(l_cmd->command->tool.tab[l_cmd->command->tool.i], &l_cmd->command->tool.check_io, l_cmd->command->tool.i);
		if (l_cmd->command->tool.result == 1 || l_cmd->command->tool.result == 3)
		{
			if (l_cmd->command->tool.cmd == 0)
				alloc_affect(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i], 1, NULL);
			else
				alloc_affect(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i], 2, NULL);
		}
		else if (l_cmd->command->tool.result == 2)
			affect_redirection(l_cmd, l_cmd->command->tool.tab[l_cmd->command->tool.i]);
		l_cmd->command->tool.i++;
	}
	l_cmd->command->s_left = tmp;
}

int			check_what_after(char c)
{
	if (c != '/' && c != '\\' && c != '|' && c != '~' &&\
		c != '\n' && (c == '\'' || c == '"' || ft_isprint(c) == 1))
		return (1);
	return (0);
}
