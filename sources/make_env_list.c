/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:27:26 by asanni            #+#    #+#             */
/*   Updated: 2024/08/14 20:00:02 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_exp	*get_last_env(t_env_exp **token)
{
	t_env_exp	*temp;

	temp = *token;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	make_tokens(t_env_exp **token, char *split)
{
	t_env_exp	*new_token;
	t_env_exp	*temp;

	new_token = malloc(sizeof(t_env_exp));
	if (new_token == NULL)
		return ;
	new_token->key = ;
	new_token->content = ;
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

//criar uma função que retorna o valor 
// key: tudo antes do =
// content: tudo depois do =
