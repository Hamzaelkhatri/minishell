/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:18:58 by zjamali           #+#    #+#             */
/*   Updated: 2020/12/01 13:16:55 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (tokens_list != NULL)
	{
		write(1, tokens_list->tk_value, ft_strlen(tokens_list->tk_value));
		write(1, "\n", 1);
		tokens_list = tokens_list->next;
	}
}
t_token	*ft_parse(char *line)
{
	int i;
	int j;
	char **token;
	t_token *tokens_list;
	t_token *temp;

	tokens_list = NULL;
	i = 0;
	j = 0;
	while(line[i])
	{
		if (line[i] == ' ' || line[i] == ';' || line[i] == '|' 
			|| line[i] == '>' )
		{
			
			temp = malloc(sizeof(t_token));
			temp->tk_value = ft_substr(line, j , i);
			temp->next = NULL;
			ft_lstadd_back(&tokens_list, temp);
			j = i + ft_strlen(temp->tk_value);
		}
		i++;
	}
	ft_printf_tokens(tokens_list);
	return tokens_list;
}