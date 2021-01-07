#include "minishell.h"

char *ft_str_in_str(const char *s1, const char *s2)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			j = 1;
			while (s2[j] && s2[j] == s1[i + j])
				j++;
			if (!s2[j] && !s1[i + j])
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}


int count_line(char **env)
{
	int i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

int search_str(char *str1, char *str2, int l1, int l2)
{
	int i;
	i = 0;

	if (l1 != l2 || l1 == 0 || l2 == 0)
		return (0);
	else if (ft_strncmp(str1, str2, l1) == 0)
		return (1);
	return (0);
}

char *ignoring_quote(char *line)
{
	int i;
	int index;
	char wich;

	i = 0;
	index = 0;
	while (line[i])
	{
		while (line[i] != 34 && line[i] != 39 && line[i])
			line[index++] = line[i++];
		if ((line[i] == 34 || line[i] == 39) && line[i])
		{
			wich = (line[i] == 34) ? 34 : 39;
			i++;
			while (line[i] != wich && line[i])
				line[index++] = line[i++];
			if (line[i] == '\0')
				line[index] = '\0';
			else
				i++;
		}
		if (line[i] == '\0')
			line[index] = '\0';
	}
	return (line);
}

char *ft_strjoin_command(t_simple_command *cmd)
{
	t_simple_command *tmp_s;
	char *line;

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
		else if (cmd->l_element->indice == 2)
		{
			line = ft_strjoin_free(line, cmd->l_element->argument);
			if (cmd->right != NULL)
				line = ft_strjoin_free(line, " ");
		}
		else if (cmd->l_element->indice == 3)
		{
			line = ft_strjoin_free(line, cmd->l_element->redirection.i_o);
			line = ft_strjoin_free(line, cmd->l_element->redirection.file);
			if (cmd->right != NULL)
				line = ft_strjoin_free(line, " ");
		}
		cmd = cmd->right;
	}
	cmd = tmp_s;
	return (line);
}

void quotes_extended(t_list_cmd *l_cmd, t_simple_command *tmp_s)
{
	while (l_cmd->command != NULL)
	{
		tmp_s = l_cmd->command->s_left;
		while (l_cmd->command->s_left != NULL)
		{
			if (l_cmd->command->s_left->l_element->indice == 1)
				l_cmd->command->s_left->l_element->cmd = ignoring_quote(l_cmd->command->s_left->l_element->cmd);
			else if (l_cmd->command->s_left->l_element->indice == 2)
				l_cmd->command->s_left->l_element->argument = ignoring_quote(l_cmd->command->s_left->l_element->argument);
			else if (l_cmd->command->s_left->l_element->indice == 3)
				l_cmd->command->s_left->l_element->redirection.file = ignoring_quote(l_cmd->command->s_left->l_element->redirection.file);
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		}
		l_cmd->command->s_left = tmp_s;
		l_cmd->command = l_cmd->command->right;
	}
}
void quotes(t_list_cmd *l_cmd)
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
		quotes_extended(l_cmd,tmp_s);
		l_cmd->command = tmp_command;
		l_cmd = l_cmd->next;
	}
	l_cmd = tmp_l_command;
}

void alloc_affect_extended(t_list_cmd **l_cmd, char *command, int indice)
{
	(*l_cmd)->command->tool.argument = 3;
	(*l_cmd)->command = add_simple_cmd((*l_cmd)->command, 3, (*l_cmd));
	if ((*l_cmd)->command->s_left->right != NULL)
		(*l_cmd)->command->s_left = (*l_cmd)->command->s_left->right;
	(*l_cmd)->command->s_left->l_element->redirection.file = ft_strdup(command);
	if (wich_redirection((*l_cmd)->command->tool.check_io) == 2)
		(*l_cmd)->command->s_left->l_element->redirection.i_o = ft_strdup(">>");
	else if (wich_redirection((*l_cmd)->command->tool.check_io) == 1)
		(*l_cmd)->command->s_left->l_element->redirection.i_o = ft_strdup(">");
	else if (wich_redirection((*l_cmd)->command->tool.check_io) == 3)
		(*l_cmd)->command->s_left->l_element->redirection.i_o = ft_strdup("<");
}
void alloc_affect(t_list_cmd *l_cmd, char *command, int indice)
{
	if (indice == 1)
	{
		l_cmd->command->tool.cmd = 1;
		l_cmd->command = add_simple_cmd(l_cmd->command, 1, l_cmd);
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		l_cmd->command->s_left->l_element->cmd = ft_strdup(command);
	}
	else if (indice == 2)
	{
		l_cmd->command->tool.argument = 2;
		l_cmd->command = add_simple_cmd(l_cmd->command, 2, l_cmd);
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		l_cmd->command->s_left->l_element->argument = ft_strdup(command);
	}
	else if (indice == 3)
		alloc_affect_extended(&l_cmd, command, indice);
}
