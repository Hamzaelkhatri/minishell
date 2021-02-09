#include "minishell.h"

int wich_redirection(int check)
{
	if (check == 5 || check == 6 || check == 7 || check == 8)
		return (2);
	else if (check == 1 || check == 2 || check == 3 || check == 4)
		return (1);
	else if (check == 9 || check == 10 || check == 11 || check == 12)
		return (3);
	return (0);
}

int check_io_redirection(char *line, int *p)
{
	int redirection;

	redirection = check_redirection(line, p);
	return (redirection);
}

int check_redirection(char *line, int *i)
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

static void affect_redirection_ex(t_list_cmd *l_cmd, int result, t_save *save)
{
	if (result == 3)
		alloc_affect(l_cmd, save->file, 3, save);
	else if (result == 4 || result == 5)
	{
		if (l_cmd->command->tool.cmd == 0)
			alloc_affect(l_cmd, save->cmd_arg, 1, NULL);
		else
			alloc_affect(l_cmd, save->cmd_arg, 2, NULL);
		if (result == 4)
		{
			alloc_affect(l_cmd, save->file, 3, save);
			l_cmd->command->tool.i++;
		}
		else if (result == 5)
			alloc_affect(l_cmd, save->file, 3, save);
	}
}

int redirection(int check_i_o)
{
	if (check_i_o == 1 || check_i_o == 5 || check_i_o == 9)
		return (2);
	else if (check_i_o == 3 || check_i_o == 7 || check_i_o == 11)
		return (3);
	else if (check_i_o == 2 || check_i_o == 6 || check_i_o == 10)
		return (4);
	else if (check_i_o == 4 || check_i_o == 8 || check_i_o == 12)
		return (5);
	return (0);
}

t_save *alloc_store(t_save *save, char *red, int which, int check_io)
{
	t_save *tmp;
	t_save *new;

	if (!(new = (t_save *)malloc(sizeof(t_save))))
		return (NULL);
	new->check = which;
	new->cmd_arg = NULL;
	new->file = NULL;
	new->check_io = check_io;
	new->result = 0;
	new->red = red;
	new->next = NULL;
	if (save == NULL)
		return (new);
	tmp = save;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (save);
}

void store(t_list_cmd *l_cmd, t_save **save, char **tab_split)
{
	int i = 0;
	int result;
	t_save *tmp;

	tmp = *save;
	// if (save->cmd_arg != NULL)
	// if (save->file != NULL)
	// if (save->red != NULL)
	while (*save)
	{
		result = redirection((*save)->check_io);
		(*save)->result = result;
		if (result == 2)
			(*save)->file = ft_strdup(l_cmd->command->tool.tab[l_cmd->command->tool.i + 1]);
		else if (result == 3)
		{
			(*save)->file = ft_strdup(tab_split[i++]);
			// printf("fiiiiile ==> %s\n",(*save)->file);
		}
		else if (result == 4)
		{
			(*save)->cmd_arg = ft_strdup(tab_split[i++]);
			(*save)->file = ft_strdup(l_cmd->command->tool.tab[l_cmd->command->tool.i + 1]);
		}
		else if (result == 5)
		{
			(*save)->cmd_arg = ft_strdup(tab_split[i++]);
			(*save)->file = ft_strdup(tab_split[i++]);
		}
		// printf("samir\n");
		*save = (*save)->next;
	}
	*save = tmp;
	// printf("|cmd-arg ==> %s|\t", (*save)->cmd_arg);
	// printf("|file ==> %s|\t", (*save)->file);
	// printf("|RED ==> %s|\n", (*save)->red);
}

void save_redirection(t_list_cmd *l_cmd, t_save *save)
{
	t_save *tmp;

	tmp = save;
	while (save)
	{
		if (save->result == 3 || save->result == 4 || save->result == 5)
			affect_redirection_ex(l_cmd, save->result, save);
		else if (save->result == 2)
		{
			alloc_affect(l_cmd, save->file, 3, save);
			l_cmd->command->tool.i++;
		}
		save = save->next;
	}
	save = tmp;
}

static int check_end(char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] == '>' || line[i - 1] == '<')
		return (1);
	else
		return (0);
}
static int check_if_redirection(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

void affect_redirection(t_list_cmd *l_cmd, char *line)
{
	char **tab_split;
	t_save *tmp;
	int i;
	char quotes;
	int check_i_o;
	t_save *save = NULL;
	int index = 0;
	int end;
	char *tmp_f;

	i = 0;
	quotes = 0;
	tab_split = NULL;
	// line = ft_strdup(line);
	if (check_end(line))
	{
		// tmp_f = line;
		line = ft_strjoin_free(line, l_cmd->command->tool.tab[++l_cmd->command->tool.i]);
		// frees(&tmp_f);
		// printf("samir\n");
		while (l_cmd->command->tool.tab[l_cmd->command->tool.i + 1] && check_end(l_cmd->command->tool.tab[l_cmd->command->tool.i + 1]))
		{
			// tmp_f = line;
			line = ft_strjoin_free(line, l_cmd->command->tool.tab[++l_cmd->command->tool.i]);
			// frees(&tmp_f);
		}
	}
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			quotes = (quotes == 0) ? 1 : 0;
		if ((line[i] == '>' || line[i] == '<') && quotes == 0 && line[i - 1] != '\\')
		{
			check_i_o = check_redirection(line, &i);
			if (check_i_o == 1 || check_i_o == 2 || check_i_o == 3 || check_i_o == 4)
			{
				if ((check_i_o == 2 || check_i_o == 4) && index == 1)
					check_i_o = (check_i_o == 2) ? 1 : 3;
				if ((check_i_o == 2 || check_i_o == 4) && index == 0)
				{
					save = alloc_store(save, ">", 1, check_i_o);
				}
				else
				{
					save = alloc_store(save, ">", 2, check_i_o);
				}
				index = 1;
			}
			else if (check_i_o == 5 || check_i_o == 6 || check_i_o == 7 || check_i_o == 8)
			{
				line[i++] = ' ';
				if ((check_i_o == 6 || check_i_o == 8) && index == 1)
					check_i_o = (check_i_o == 6) ? 5 : 7;
				if ((check_i_o == 6 || check_i_o == 8) && index == 0)
					save = alloc_store(save, ">>", 1, check_i_o);
				else
					save = alloc_store(save, ">>", 2, check_i_o);
				index = 1;
			}
			else
			{
				if ((check_i_o == 10 || check_i_o == 12) && index == 1)
					check_i_o = (check_i_o == 10) ? 9 : 11;
				if ((check_i_o == 10 || check_i_o == 12) && index == 0)
					save = alloc_store(save, "<", 1, check_i_o);
				else
					save = alloc_store(save, "<", 2, check_i_o);
				index = 1;
			}
			line[i] = ' ';
		}
		i++;
	}
	tab_split = ft_space_split_quote(line);
	store(l_cmd, &save, tab_split);
	save_redirection(l_cmd, save);
	// while (save)
	// {
	// 	// if (save->cmd_arg != NULL)
	// 		printf("|cmd-arg ==> %s|\t", save->cmd_arg);
		// if (save->file != NULL)
			// printf("|file ==> %s|\t", save->file);
		// if (save->red != NULL)
			// printf("|RED ==> %s|\n", save->red);
	// 	save = save->next;
	// }
	// for free
	// if (save->cmd_arg != NULL)
		// frees(&save->cmd_arg);
	// if (save->file != NULL)
		// frees(&save->file);
	// 	frees(&save->red);
	// free(save);
		// frees(&save->red);
	// if (save->red != NULL)
	// {
	// 	printf("|RED ==> %s|\n", save->red);
	// 	frees(&save->red);
	// 	printf("|RED ==> %s|\n", save->red);
	// }
	// free(save);
	// save = NULL;
	frees(&line);
	free_redirection(&save);
	free_tab(&tab_split);
}

// 3/4
// 7/8
// 11/12
// arguements 2/4 6/8 10/12

// result 2  no argument without file
// result 3  no argument with file
// result 4	 with argument and without file
// result 5  with arguement and with file
