/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:48:35 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/15 15:00:23 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		read_line(char **line)
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

void	bash_promp(void)
{
	ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 2);
}

void	sort_execute(t_list_cmd *cmd, t_path *path)
{
	sort(cmd);
	variables(cmd, path);
	check_scommand(cmd);
	commande_effect(cmd, path);
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
