/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokennizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:48 by asanni            #+#    #+#             */
/*   Updated: 2024/07/20 19:23:15 by asanni           ###   ########.fr       */
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
	new_token->type = find_etype(*token, split);
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

int	find_etype(t_token *token, char *str)
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

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		printf("Token: |%s| -> Type: %d,\n", current->str, current->type);
		current = current->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		printf("cmd: |%s| -> option: %s,\n", current->str, current->options[i]);
		i++;
		current = current->next;
	}
}
