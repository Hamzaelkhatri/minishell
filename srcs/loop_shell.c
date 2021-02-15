/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:16:32 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/15 15:46:12 by helkhatr         ###   ########.fr       */
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
		empty_exit(&line);
		(line[ret - 1] != '\n') ? manage_d(&lines, line) : 0;
		if (lines && g_var1 && line[ret - 1] == '\n')
		{
			tmp = lines;
			lines = ft_strjoin(lines, line);
			frees(&tmp);
			tmp = line;
			line = ft_strdup(lines);
			frees(&tmp);
			init_2(&lines);
		}
		check = set_new_cmd(line, cmd, path);
		frees(&line);
	}
}

void	exit_(char **line)
{
	frees(&*line);
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

void	manage_cntrc(char *line)
{
	if ((g_var == 111 || g_var == 112) && line[0] != '\n')
		ft_putendl_fd("", 1);
}
