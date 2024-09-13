/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:48 by asanni            #+#    #+#             */
/*   Updated: 2024/09/13 19:46:42 by asanni           ###   ########.fr       */
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

int	has_token_type(t_mini minishell, int type_to_find)
{
	t_token	*current_token;

	current_token = minishell.token;
	while (current_token != NULL)
	{
		if (current_token->type == type_to_find)
			return (1);
		current_token = current_token->next;
	}
	return (0);
}

int	count_token_type(t_mini *minishell, int type_to_count)
{
	t_token	*current_token;
	int		count;

	current_token = minishell->token;
	count = 0;
	while (current_token != NULL)
	{
		if (current_token->type == type_to_count)
			count++;
		current_token = current_token->next;
	}
	return (count);
}
