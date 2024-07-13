/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokennizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:48 by asanni            #+#    #+#             */
/*   Updated: 2024/07/13 14:31:45 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_tokens(t_token *token, char *split)
{
	t_token	*new_token;

	if (token == NULL)
		printf("O token fornecido não pode ser NULL.\n");
	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		error_function("Erro na alocação de memória para o novo token.");
	new_token->str = split;
	new_token->type = find_etype(split);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (token->next != NULL)
	{
	new_token->next = token->next;
	new_token->next->prev = new_token;
	token->next = new_token;
	new_token->prev = token;
	}
	else
	{
	token->next = new_token;
	new_token->prev = token;
	}
}

int	find_etype(char *str)
{
	if (str[0] == '$')
		return (VAR);
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
	else if (ft_strcmp(str, "\0") == 0)
		return (END);
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
