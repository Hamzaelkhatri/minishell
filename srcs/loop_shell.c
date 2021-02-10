/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:16:32 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/10 18:52:30 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_path *path, t_list_cmd *cmd)
{
	char	*line;
	int		check;

	init_(&line, &check);
	while (1)
		looping_exec(path, cmd, &check);
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
	if (sig == SIGQUIT)
		g_var = 111;
}

void	manage_cntrc(char *line)
{
	if (g_var == 111 && line[0] != '\n')
		ft_putendl_fd("", 1);
}
