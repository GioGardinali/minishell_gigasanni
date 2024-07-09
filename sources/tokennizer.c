/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokennizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:48 by asanni            #+#    #+#             */
/*   Updated: 2024/07/09 14:17:11 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_tokens(t_token **token, char *split)
{
	t_token	*new_token;
	t_token	*tmp;

	if (token == NULL)
		error_function("error in tokenizer");
	new_token = (malloc(sizeof(t_token)));
	if (new_token == NULL)
		error_function("error in tokenizer");
	new_token->str = split;
	new_token->type = find_etype(split);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (*token == NULL)
	{
		*token = new_token;
		return ;
	}
	else
	{
		tmp = *token;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
}

int	find_etype(char	*str)
{
	if (str[1] == '$')
		return (VAR);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '>')
		return (TRUNC);
	else if (*str == '>>')
		return (APPEND);
	else if (*str == '<')
		return (INPUT);
	else if (*str == '<<')
		return (HERE_DOC);
	else
		return (WORD);
}
