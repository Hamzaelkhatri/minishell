/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:16:32 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/09 18:31:50 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <setjmp.h>

int		g_var;
int		g_var1;

int		read_line(t_path *key, char **line)
{
	int	ret;

	ret = 0;
	*line = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!line)
	{
		ft_putendl_fd("\e[1;31m bash$ : allocation error\e[0;37m", 1);
		exit(1);
	}
	if ((ret = read(0, *line, BUFFER_SIZE)) == -1)
	{
		if (line[BUFFER_SIZE] == 0)
			exit(0);
		else
			exit(1);
	}
	return (ret);
}

void	sigint_handler(int sig)
{
	int a;

	if (sig == SIGINT)
	{
		if (g_var)
			ft_putstr_fd("\n\e[1;32mbash$ \e[0;37m", 2);
		g_var = 111;
		g_var1 = 0;
	}
	if (sig == SIGQUIT)
		g_var = 111;
}

void	bash_promp(void)
{
	ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 2);
}

void	signals(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cnrtl-C", 2);
	if (signal(SIGQUIT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cntrl-\\", 2);
	bash_promp();
}

void	exit_(char **line)
{
	frees(line);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}

void	manage_cntrc(char *line)
{
	if (g_var == 111 && line[0] != '\n')
		ft_putendl_fd("", 1);
}

void	sort_execute(t_list_cmd *cmd, t_path *path)
{
	sort(cmd);
	variables(cmd, path);
	check_scommand(cmd);
	commande_effect(cmd, path);
}

void	manage_line(t_path *path, int *check, t_list_cmd *cmd, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	g_var = 0;
	path->cmds = line;
	if (*check != 0)
		while (line[i] && (line[i] < 33) && line[i] != '\n')
			i++;
	if (line[i] != '\n' && i != ft_strlen(line))
	{
		path->cmds = ft_strtrim(path->cmds, "\n");
		*check = ft_check_line(path->cmds);
	}
	if (!*check)
	{
		cmd = add_list_cmd(cmd);
		tmp = path->cmds;
		cmd->line = ft_strdup(path->cmds);
		parse_list_command(cmd, cmd->line);
		ft_strdel(&path->cmds);
		sort_execute(cmd, path);
		free_lcommand(&cmd);
	}
}

void	manage_d(char **lines, char *line)
{
	if (*lines)
		*lines = ft_strjoin(*lines, line);
	else
		*lines = ft_strdup(line);
	g_var1 = 1;
}

int		manage_spaces(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] < 33)
		i++;
	if (line[i] == '\n')
		return (0);
	else
		return (1);
}

int		set_new_cmd(char **lines, char *line, t_list_cmd *cmd, t_path *path)
{
	int check;

	check = 0;
	if (line[0] == '\n' || !manage_spaces(line))
	{
		check = -1;
		g_var1 = 0;
	}
	if (!g_var1)
	{
		manage_line(path, &check, cmd, line);
		manage_cntrc(line);
		bash_promp();
		g_var = 11;
	}
	return (check);
}

void	init_(char **lines, int *check)
{
	g_var = 0;
	*lines = NULL;
	g_var1 = 0;
	*check = 0;
	signals();
}

void	loop_shell(t_path *path, t_list_cmd *cmd)
{
	char	*line;
	int		ret;
	char	*lines;
	int		check;
	char	*tmp;

	lines = NULL;
	g_var = 0;
	init_(&line, &check);
	while (1)
	{
		g_var = 0;
		if (check > 0)
			path->dollar = check;
		check = 0;
		ret = read_line(path, &line);
		if (line[0] == '\0' && !g_var1)
			exit_(&line);
		if (line[ret - 1] != '\n')
			manage_d(&lines, line);
		else if (lines && g_var1)
		{
			tmp = lines;
			lines = ft_strjoin(lines, line);
			frees(&tmp);
			line = ft_strdup(lines);
			frees(&lines);
			g_var1 = 0;
		}
		check = set_new_cmd(&lines, line, cmd, path);
		check = 0;
		frees(&line);
	}
}
