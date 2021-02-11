/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:16:32 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 18:57:08 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_path *path, t_list_cmd *cmd)
{
	char	*lines;
	char	*line;
	int		ret;
	char	*tmp;
	int		check;

	init_(&lines);
	while (1)
	{
		ret = read_line(&line);
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
			init_2(&lines);
		}
		check = set_new_cmd(&lines, line, cmd, path);
		frees(&line);
	}
}

void	exit_(char **line)
{
	frees(line);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}

void	signals(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cnrtl-C", 2);
	if (signal(SIGQUIT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n\e[1;31m can't catch cntrl-\\", 2);
	bash_promp();
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_var)
			ft_putstr_fd("\n\e[1;32mbash$ \e[0;37m", 2);
		g_var = 111;
		g_var1 = 0;
	}
	if (sig == SIGQUIT && g_var2)
	{
		g_var = 112;
		g_var2 = 0;
		ft_putstr_fd("QUIT : 3", 2);
	}
}

void	manage_cntrc(char *line, t_path *path)
{
	if ((g_var == 111 || g_var == 112) && line[0] != '\n')
		ft_putendl_fd("", 1);
}
