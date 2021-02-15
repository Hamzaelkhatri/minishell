/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:23:48 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/15 15:49:30 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_in(char *str, int i, int save)
{
	if ((str[i] == '$' && (((ft_isalnum(str[i + 1]) || str[i + 1] == '_' ||
		str[i + 1] == '?' || (str[i + 1] == 34 && save == 0) ||\
		str[i + 1] == 39) && str[i + 1] != '$' && str[i + 1] != '\\' &&\
		str[i + 1] && !(str[i + 1] == 34 && save == 1))))\
		&& count_antislach(str, i - 1))
		return (1);
	return (0);
}

int	norm_i(int *i)
{
	if (*i < 0)
		*i = 0;
	return (*i);
}
