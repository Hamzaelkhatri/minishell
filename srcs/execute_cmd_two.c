/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:12:40 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/15 15:33:21 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commandes(char *cmd, t_path *path, t_command *l_cmd)
{
	if (!ft_check_str("exit", cmd))
		cmd = word_tolower(cmd);
	if (!ft_strcmp(cmd, "pwd"))
		execute_pwd(path);
	else if (!ft_strcmp(cmd, "env"))
		execute_env(path);
	else if (!ft_strcmp(cmd, "cd"))
		execute_cd(l_cmd, path);
	else if (!ft_strcmp(cmd, "exit"))
		exit_exec(l_cmd);
	else if (!ft_strcmp(cmd, "export") && l_cmd->s_left->right == NULL)
		execute_export(path);
	else if (!ft_strcmp(cmd, "export") && l_cmd->s_left->right != NULL)
		execute_export_(path, l_cmd);
	else if (!ft_strcmp(cmd, "unset") && l_cmd->s_left->right != NULL)
		execute_unset(path, l_cmd);
	else if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "echo -n"))
		execute_echo(cmd, path, l_cmd);
}

char	*get_file_shift(t_command *lcmd, char *shift)
{
	t_simple_command	*cmd;

	cmd = lcmd->s_left;
	while (cmd)
	{
		if (cmd->l_element->indice == 3 && !ft_strcmp(
					cmd->l_element->redirection.i_o, shift)
				&& ft_strcmp("<", shift) && cmd->right == NULL)
			return (cmd->l_element->redirection.file);
		else if (cmd->l_element->indice == 3 &&
				!ft_strcmp(cmd->l_element->redirection.i_o, shift)
				&& !ft_strcmp("<", shift)
				&& ft_strcmp(cmd->right->l_element->redirection.i_o, "<"))
			return (cmd->l_element->redirection.file);
		else if (cmd->l_element->indice == 3 &&
				ft_strcmp(cmd->l_element->redirection.i_o, "<") &&
				cmd->right && cmd->right->l_element->redirection.file &&
				ft_strcmp(cmd->l_element->redirection.i_o, ">>"))
			create_file(cmd->l_element->redirection.file);
		cmd = cmd->right;
	}
	return (NULL);
}

char	*get_file(t_command *lcmd)
{
	t_simple_command *cmd;

	cmd = lcmd->s_left;
	while (cmd)
	{
		if (cmd->l_element->indice == 3 && cmd->right == NULL)
			return (cmd->l_element->redirection.file);
		cmd = cmd->right;
	}
	return (NULL);
}

int		create_file(char *file)
{
	int fd;

	fd = open(file,
O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	ft_putstr_fd("", fd);
	close(fd);
	return (0);
}

char	*get_shift(t_command *lcmd)
{
	t_simple_command	*cmd;

	cmd = lcmd->s_left;
	while (cmd)
	{
		if (cmd->l_element->indice == 3 && (cmd->right == NULL ||
		!ft_strcmp(cmd->l_element->redirection.i_o, ">>")))
			return (cmd->l_element->redirection.i_o);
		else if (cmd->l_element->indice == 3 &&
				ft_strcmp(cmd->l_element->redirection.i_o, "<") &&
				ft_strcmp(cmd->l_element->redirection.i_o, ">>"))
			create_file(cmd->l_element->redirection.file);
		cmd = cmd->right;
	}
	return (NULL);
}
