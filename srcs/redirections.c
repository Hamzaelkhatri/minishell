/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:32:55 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/12 09:33:38 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		double_red(char *file1, char *file2)
{
	int		in;
	int		out;

	in = open(file2, O_RDONLY);
	out = open(file1, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP
			| S_IWUSR);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (0);
}
