/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:02:30 by zjamali           #+#    #+#             */
/*   Updated: 2021/01/25 17:46:19 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **delete_quote(char **line)
{
	int i;
	int j;
	int index;
	char wich;

	i = 0;
	while (line[i])
	{
		j = 0;
		index = 0;
		while (line[i][j])
		{
			while (line[i][j] != 34 && line[i][j] != 39 && line[i][j])
				line[i][index++] = line[i][j++];
			if ((line[i][j] == 34 || line[i][j] == 39) && line[i][j])
			{
				wich = (line[i][j] == 34) ? 34 : 39;
				j++;
				while (line[i][j] != wich && line[i][j])
					line[i][index++] = line[i][j++];
				if (line[i][j] == '\0')
					line[i][index] = '\0';
				else
					j++;
			}
			if (line[i][j] == '\0')
				line[i][index] = '\0';
		}
		i++;
	}
	return (line);
}

bool check_quote(char *line)
{
	int i;
	int check;
	char wich;

	check = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			wich = (line[i] == 34) ? 34 : 39;
			i++;
			check = 0;
			while (line[i])
			{
				if (line[i] == wich)
				{
					check = 1;
					break;
				}
				i++;
			}
			if (check != 1)
				return (false);
		}
		if (line[i])
			i++;
	}
	return (true);
}

void ft_nhaydo_nl(char **tab)
{
	int count;
	int len;

	count = ft_2strlen(tab);
	len = ft_strlen(tab[count - 1]);
	tab[count - 1][len - 1] = '\0';
}

void echo(char *line, t_path *path)
{
	line = ft_strtrim(line,"\n");
	if(!ft_strncmp(line,"$",1) && get_var_env(path,line))
	{
		ft_putstr_fd(get_var_env(path,line),1);
	}
	else
	{
		ft_putstr_fd(line,1);
	}
	
}
