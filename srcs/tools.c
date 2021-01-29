#include "minishell.h"

int		search_str(char *str1, char *str2, int l1, int l2)
{
	int	i;

	i = 0;
	if (l1 != l2 || l1 == 0 || l2 == 0)
		return (0);
	else if (ft_strncmp(str1, str2, l1) == 0)
		return (1);
	return (0);
}

void	ignoring_quote_ext(char *line, int *i, int *index)
{
	char	wich;

	wich = (line[*i] == 34) ? 34 : 39;
	(*i)++;
	while (((line[*i] == '\\' && line[*i + 1] == wich) ||\
				line[*i] != wich) && line[*i])
	{
		if (line[*i] == '\\' && line[*i + 1] == wich)
			(*i)++;
		line[(*index)++] = line[(*i)++];
	}
	if (line[*i] == '\0')
		line[(*index)] = '\0';
	else
		(*i)++;
}

char	*ignoring_quote(char *line)
{
	int		i;
	int		index;
	char	wich;

	i = 0;
	index = 0;
	while (line[i])
	{
		while ((line[i] == '\\' && (line[i + 1] == 34 || line[i + 1] == 39))\
				|| (line[i] != 34 && line[i] != 39 && line[i]))
		{
			if (line[i] == '\\' && (line[i + 1] == 34 || line[i + 1] == 39))
				i++;
			line[index++] = line[i++];
		}
		if ((line[i] == 34 || line[i] == 39) && line[i])
			ignoring_quote_ext(line, &i, &index);
		if (line[i] == '\0')
			line[index] = '\0';
	}
	return (line);
}

void	ft_strjoin_cmd_ext(t_simple_command *cmd, char **line)
{
	if (cmd->l_element->indice == 2)
	{
		*line = ft_strjoin_free(*line, cmd->l_element->argument);
		if (cmd->right != NULL)
			*line = ft_strjoin_free(*line, " ");
	}
	// else if (cmd->l_element->indice == 3)
	// {
	// 	*line = ft_strjoin_free(*line, cmd->l_element->redirection.i_o);
	// 	*line = ft_strjoin_free(*line, cmd->l_element->redirection.file);
	// 	if (cmd->right != NULL)
	// 		*line = ft_strjoin_free(*line, " ");
	// }
}

char	*ft_strjoin_command(t_simple_command *cmd)
{
	t_simple_command	*tmp_s;
	char				*line;

	line = ft_strdup("\0");
	tmp_s = cmd;
	while (cmd != NULL)
	{
		if (cmd->l_element->indice == 1)
		{
			line = ft_strjoin_free(line, cmd->l_element->cmd);
			if (cmd->right != NULL)
				line = ft_strjoin_free(line, " ");
		}
		else
			ft_strjoin_cmd_ext(cmd, &line);
		cmd = cmd->right;
	}
	cmd = tmp_s;
	return (line);
}
