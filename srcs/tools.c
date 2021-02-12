/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:51:04 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/11 18:51:05 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_str(char *str1, char *str2, int l1, int l2)
{
	int	i;

	i = 0;
	if (l1 != l2 || l1 == 0 || l2 == 0)
		return (0);
	else if (ft_strncmp(str1, str2, l1) == 0)
		return (1);
	return (0);
}

void	ft_strjoin_cmd_ext(t_simple_command *cmd, char **line)
{
	if (cmd->l_element->indice == 2)
	{
		*line = ft_strjoin_free(*line, cmd->l_element->argument);
		if (cmd->right != NULL)
			*line = ft_strjoin_free(*line, " ");
	}
}

char	*ft_strjoin_command(t_simple_command *cmd)
{
	t_simple_command	*tmp_s;
	char				*line;
	char				*tmp;

	line = NULL;
	tmp_s = cmd;
	while (cmd != NULL)
	{
		if (cmd->l_element->indice == 1)
		{
			line = ft_strjoin_free(line, cmd->l_element->cmd);
			tmp = line;
			if (cmd->right != NULL)
			{
				line = ft_strjoin_free(line, " ");
				frees(&tmp);
				tmp = line;
			}
		}
		else
			ft_strjoin_cmd_ext(cmd, &line);
		cmd = cmd->right;
	}
	cmd = tmp_s;
	return (line);
}

int		count_antislach(char *line, int i)
{
	int	j;
	int	result;

	j = 0;
	if (i < 0)
		return (1);
	while (line[i] == '\\' && i >= 0)
	{
		i--;
		j++;
	}
	result = j % 2;
	if (result == 0)
		return (1);
	else
		return (0);
}

void	*leak(char **spl, int j)
{
	j = j - 1;
	while (spl[j])
	{
		free(spl[j]);
		j--;
	}
	free(spl);
	return (NULL);
}
