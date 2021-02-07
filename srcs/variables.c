
#include "minishell.h"

char *ft_extraire_variable(char *line, int i, int *index)
{
	int result;
	char *str;
	int j;
	int k;

	j = 0;
	k = 0;
	result = *index + 2;
	str = (char *)malloc(result);
	while (j < *index + 1)
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}
int ft_check_variable(char *line, int i)
{
	int j;

	j = 0;
	i++;
	if (line[i] == '$')
		return (0);
	else if (line[i] == '?')
		return (1);
	while (ft_isalnum(line[i]) || line[i] == '_')
	{
		i++;
		j++;
	}
	return (j);
}

char *ft_variables(char *line, int i, int *index)
{
	char *str;

	str = NULL;
	*index = ft_check_variable(line, i);
	if (*index == 0)
		return (NULL);
	else
		str = ft_extraire_variable(line, i, index);
	return (str);
}

char *ft_strdup_beg(const char *s1, int j)
{
	int i;
	char *ptr;

	i = 0;
	if (!(ptr = malloc(sizeof(char) * (j))))
		return (NULL);
	while (i < j)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char *ft_concatenation(char *line, int *i, int index, char *ptr)
{
	char *str1;
	char *str_beg;
	char *str_end;
	int len;
	char *tmp;

	str_beg = NULL;
	str_end = NULL;
	str1 = (ptr != NULL) ? ft_strdup(ptr) : ft_strdup("");
	len = ft_strlen(str1);
	if (*i != 0)
	{
		str_beg = ft_strdup_beg((line), *i);
		str1 = ft_strjoin_free(str_beg, str1);
	}
	if (line[*i + 1 + index])
	{
		str_end = ft_strdup(&line[*i + index + 1]);
		str1 = ft_strjoin_free(str1, (str_end));
		// tmp = str_end;
		free(str_end);
		str_end = NULL;
	}
	*i = len + *i - 1;
	// free(tmp);
	return (str1);
}

// char *affectation_$(char **line,int *i, int *index, t_path *path)
char *dollars(char *line, t_path *path)
{
	int i;
	int index;
	char *ptr;
	char *str;
	int save = 0;
	char *samir;

	i = 0;
	index = 0;
	samir = ft_strdup(line);
	while (samir[i])
	{
		if (samir[i] == 34 && count_antislach(samir, i - 1))
			save = (save == 0) ? 1 : 0;
		if (samir[i] == 39 && count_antislach(samir, i - 1) && save == 0)
		{
			i++;
			while (samir[i] != 39 && samir[i])
				i++;
		}
		else if (samir[i] == '$' && count_antislach(samir, i - 1))
		{

			if ((str = ft_variables(samir, i, &index)))
			{
				if (str[0] == '$' && str[1] == '?' && str[2] == '\0')
				{
					ptr = ft_itoa(path->dollar);
					samir = ft_concatenation(samir, &i, index, ptr);
				}
				else
				{
					ptr = (get_var_env1(path, str)) ? ft_strdup(get_var_env1(path, str)) : NULL;
					if (ptr != NULL)
					{
						samir = ft_concatenation(samir, &i, index, ptr);
						free(ptr);
					}
					else
						samir = ft_concatenation(samir, &i, index, NULL);
				}
			}
		}
		if (samir[i])
			i++;
	}
	// free(line);
	// printf("line { ===> %s}\n",line);

	return ((samir));
}

void variables_extended(t_list_cmd *l_cmd, t_simple_command *tmp_s, t_path *path)
{
	char *tmp;

	while (l_cmd->command != NULL)
	{
		tmp_s = l_cmd->command->s_left;
		while (l_cmd->command->s_left != NULL)
		{
			if (l_cmd->command->s_left->l_element->indice == 1)
			{
				tmp = ft_strdup(l_cmd->command->s_left->l_element->cmd);
				tmp = dollars(tmp, path);
				free(l_cmd->command->s_left->l_element->cmd);
				l_cmd->command->s_left->l_element->cmd = NULL;
				l_cmd->command->s_left->l_element->cmd = ft_ignoring(tmp);
				free(tmp);
			}
			else if (l_cmd->command->s_left->l_element->indice == 2)
			{
				tmp = ft_strdup(l_cmd->command->s_left->l_element->argument);
				tmp = dollars(tmp, path);
				free(l_cmd->command->s_left->l_element->argument);
				l_cmd->command->s_left->l_element->argument = NULL;
				l_cmd->command->s_left->l_element->argument = ft_ignoring(tmp);
				free(tmp);
			}
			else if (l_cmd->command->s_left->l_element->indice == 3)
			{
				tmp = ft_strdup(l_cmd->command->s_left->l_element->redirection.file);
				tmp = dollars(tmp, path);
				// 	free(l_cmd->command->s_left->l_element->redirection.file);
				// l_cmd->command->s_left->l_element->redirection.file = NULL;
				l_cmd->command->s_left->l_element->redirection.file = ft_ignoring(tmp);
				free(tmp);
			}
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		}
		l_cmd->command->s_left = tmp_s;
		l_cmd->command = l_cmd->command->right;
	}
}

void variables(t_list_cmd *l_cmd, t_path *path)
{
	t_list_cmd *tmp_l_command;
	t_command *tmp_command;
	t_simple_command *tmp_s;

	tmp_l_command = l_cmd;
	tmp_command = l_cmd->command;
	tmp_s = l_cmd->command->s_left;
	while (l_cmd != NULL)
	{
		tmp_command = l_cmd->command;
		tmp_s = l_cmd->command->s_left;
		variables_extended(l_cmd, tmp_s, path);
		l_cmd->command = tmp_command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp_l_command;
}