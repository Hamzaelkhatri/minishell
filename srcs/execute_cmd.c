/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:24:47 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/13 16:09:40 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_tolower(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	free_cmd(int index, char **cmd)
{
	if (index == 2 && cmd)
	{
		free(*cmd);
		*cmd = NULL;
	}
}

int		ft_check_str(char *cmd, char *des)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ft_tolower(des[i]))
			return (0);
		i++;
	}
	return (1);
}

int		get_cmd_(char *cmd, t_path *path, t_command *l_cmd)
{
	char		*tmp1;
	char		*tmp2;
	t_command	*tmp;
	char		*tcmp;

	tcmp = ft_strtrim(cmd, "\n");
	if (get_shift(l_cmd))
	{
		tmp = l_cmd;
		tmp1 = get_file(tmp);
		tmp2 = get_shift(tmp);
		shift_extra(tmp1, tmp2, path, tmp);
	}
	else if (cmdcheck(tcmp))
		commandes(tcmp, path, l_cmd);
	else
		execute(path, l_cmd);
	frees(&tcmp);
	return (path->dollar);
}
