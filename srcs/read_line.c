/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:16:32 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/12 09:32:11 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		manage_line(t_path *path, int check, t_list_cmd *cmd, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	g_var = 0;
	path->cmds = ft_strtrim(line, "\n");
	if (check != 0)
		while (line[i] && (line[i] < 33) && line[i] != '\n')
			i++;
	if (line[i] != '\n' && i != ft_strlen(line))
	{
		check = ft_check_line(path->cmds);
		path->dollar = (check > 0) ? check : path->dollar;
	}
	if (!check)
	{
		cmd = add_list_cmd(cmd);
		tmp = path->cmds;
		cmd->line = ft_strdup(path->cmds);
		parse_list_command(cmd, cmd->line);
		ft_strdel(&path->cmds);
		sort_execute(cmd, path);
		free_lcommand(&cmd);
	}
	return (check);
}

void	manage_d(char **lines, char *line)
{
	if (*lines)
		*lines = ft_strjoin(*lines, line);
	else
		*lines = ft_strdup(line);
	g_var1 = 1;
}

int		set_new_cmd(char **lines, char *line, t_list_cmd *cmd, t_path *path)
{
	int check;

	check = 0;
	if (g_var == 111)
		path->dollar = 1;
	if (line[0] == '\n' || !manage_spaces(line))
	{
		check = -1;
		g_var1 = 0;
	}
	if (!g_var1)
	{
		check = manage_line(path, check, cmd, line);
		manage_cntrc(line, path);
		if (g_var == 112)
			path->dollar = 131;
		bash_promp();
		g_var = 11;
	}
	return (check);
}

void	init_(char **lines)
{
	g_var = 1;
	*lines = NULL;
	g_var2 = 1;
	g_var1 = 0;
	signals();
}
