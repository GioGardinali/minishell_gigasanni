/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:48 by asanni            #+#    #+#             */
/*   Updated: 2024/07/25 15:30:02 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*get_last_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	make_tokens(t_token **token, char *split)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return ;
	new_token->str = split;
	new_token->type = find_etype(split);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!*token)
	{
		*token = new_token;
		return ;
	}
	temp = get_last_token(token);
	temp->next = new_token;
	new_token->prev = temp;
}

int	find_etype(char *str)
{
	if (str[0] == '$')
		return (VAR);
	else if (str[0] == '\"')
		return (QUOTES);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">") == 0)
		return (TRUNC);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(str, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(str, "<<") == 0)
		return (HERE_DOC);
	else
		return (WORD);
}
