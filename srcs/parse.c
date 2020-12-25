/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:18:58 by zjamali           #+#    #+#             */
/*   Updated: 2020/12/25 14:54:23 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "minishell.h"

t_token *ft_lstlast(t_token *lst)
{	
	if(lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token *temp;

	if (*alst)
	{
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else
		*alst = new;
}

void ft_printf_tokens(t_token *tokens_list)
{
	int i ;

	while (tokens_list != NULL)
	{
		write(1, "{", 1);
		write(1, tokens_list->token, ft_strlen(tokens_list->token));
		write(1, "}", 1);
		write(1, "\n", 1);
		tokens_list = tokens_list->next;
	}
}

t_token	*ft_parse(char *line)
{
	int i;
	t_token *tokens_list;
	t_token *tmp;
	char **split;

	i = 0;
	tokens_list = NULL;
	split = ft_space_split(line);
	while (split[i])
	{
		if (!(tmp = (t_token*)malloc(sizeof(t_token))))
			ft_putstr_fd("allocation error.",1);
		ft_memset((void*)tmp,0,sizeof(t_token));
		tmp->token = split[i];
		tmp->next = NULL;
		ft_lstadd_back(&tokens_list,tmp);
		i++;
	}
	//ft_printf_tokens(tokens_list);
	return (tokens_list);
}