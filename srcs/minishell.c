/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:49:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/10 18:56:21 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_list_cmd		*l_command;
	t_path			path;
	t_key			key;
	t_cmd			cmds;
	t_list_cmd		*cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	l_command = NULL;
	init(&path, &key, &cmds);
	path.env->fullenv = env;
	loop_shell(&path, cmd);
	return (0);
}
