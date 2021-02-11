/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:30:22 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 10:31:46 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmdcheck(char *str)
{
	char	*cmd[10];
	int		i;

	i = 0;
	cmd[0] = "echo";
	cmd[1] = "exit";
	cmd[2] = "env";
	cmd[3] = "export";
	cmd[4] = "unset";
	cmd[5] = "pwd";
	cmd[6] = "cd";
	cmd[7] = "echo -n";
	cmd[8] = NULL;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], str))
			return (1);
		i++;
	}
	return (0);
}
