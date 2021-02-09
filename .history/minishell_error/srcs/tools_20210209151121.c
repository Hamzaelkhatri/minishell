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
	int p = 0;

	// printf("sassaas\n");
	wich = line[*i];
	(*i)++;
	// printf("{%c}\n",wich);
	while ((((line[*i] == wich && count_antislach(line, *i - 2) == 0)) || line[*i] != wich) && line[*i])
	{
		line[(*index)++] = line[(*i)++];
	}
	if(line[*i] == wich)
		line[(*index)] = line[++(*i)];
	// if (line[*i] == '\0')
	// 	line[(*index)] = '\0';
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
		while ((count_antislach(line, i - 1) == 0 && (line[i] == 34 || line[i] == 39))\
				|| (line[i] != 34 && line[i] != 39 && line[i]))
		{
			// printf("line[%d] ==> %c\n",i,line[i]);
			line[index++] = line[i++];
		}
		if (line[i] == 34  && line[i])
			ignoring_quote_ext(line, &i, &index);
		if(line[i] == 39 && line[i])
		{
			line[index++] = line[i++];
			while(line[i] != 39 && line[i])
				line[index++] = line[i++];
		}
		else if (line[i] == '\0')
			line[index] = '\0';
	}
	return (line);
}

void	ft_strjoin_cmd_ext(t_simple_command *cmd, char **line)
{
	if (cmd->l_element->indice == 2)
	{
		*line = ft_strjoin(*line, cmd->l_element->argument);
		if (cmd->right != NULL)
			*line = ft_strjoin(*line, " ");
	}
}

char	*ft_strjoin_command(t_simple_command *cmd)
{
	t_simple_command	*tmp_s;
	char				*line;
	char				*tmp;

	line = NULL;
	tmp_s = cmd;
	while (cmd != NULL)
	{
		if (cmd->l_element->indice == 1)
		{
			line = ft_strjoin_free(line, cmd->l_element->cmd);
			tmp = line;
			if (cmd->right != NULL)
			{
				frees(&tmp);
				line = ft_strjoin_free(line, " ");
				tmp = line;
			}
			frees(&tmp);
		}
		else
			ft_strjoin_cmd_ext(cmd, &line);
		cmd = cmd->right;
	}
	cmd = tmp_s;
	return (line);
}
