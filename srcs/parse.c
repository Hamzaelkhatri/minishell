/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:18:58 by zjamali           #+#    #+#             */
/*   Updated: 2020/12/07 19:43:52 by zjamali          ###   ########.fr       */
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

	//i  = 0;
	//while (tokens_list != NULL)
	//{
	//	i++;
	//	tokens_list = tokens_list->next;
	//}
	//printf("%d",i);
	while (tokens_list != NULL)
	{
		write(1, "{", 1);
		write(1, tokens_list->token, ft_strlen(tokens_list->token));
		write(1, "}", 1);
		write(1, "\n", 1);
		tokens_list = tokens_list->next;
	}
}

char *char_to_str(char c)
{
	char *str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_add_char_to_str(char *str,char ch)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (str)
	{
		p = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (p == NULL)
			return (NULL);
		while (str[j])
			p[i++] = str[j++];
		p[i++] = ch;
		p[i] = '\0';
		return (p);
	}
	else
	{
		p = (char *)malloc(sizeof(char) * (2));
		p[i++] = ch;
		p[i] = '\0';
		return (p);
	}
}

char	*ft_get_cmd(char *line ,int *i)
{
	int j;
	char *cmd;

	j = *i;
	while (line[j] && (ft_isalpha(line[j])|| ft_isdigit(line[j]) || line[j] == '-' || line[j] == '|'))
	{
		cmd = ft_add_char_to_str(cmd,line[j]);
		j++;
	}
	*i = j;
	return (cmd);
}
t_token	*ft_parse(char *line)
{
	int i;
	int j;
	char *token;
	t_token *tokens_list;
	t_token *temp;
	char *str;

	str = NULL;
	tokens_list = NULL;
	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		while(line[i] == ' ' || line[i] == '\t')
			i++;
		str = ft_get_cmd(line,&i);
		if (str && ft_isalpha(str[0]))
		{
			temp = (t_token*)malloc(sizeof(t_token));
			temp->token =str;
			temp->next = NULL;
			str = NULL;
			ft_lstadd_back(&tokens_list, temp);
		}
		i++;
	}
	ft_printf_tokens(tokens_list);
	return (tokens_list);
}