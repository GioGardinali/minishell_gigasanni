/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:27:26 by asanni            #+#    #+#             */
/*   Updated: 2024/08/16 19:07:35 by asanni           ###   ########.fr       */
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

char	**return_pair(char **env)
{
	ft_split();
}

void	list_env(t_env_exp **token, char *split)
{
	t_env_exp	*env_pair;
	t_env_exp	*temp;

	env_pair = malloc(sizeof(t_env_exp));
	if (env_pair == NULL)
		return ;
	env_pair->key = ;
	env_pair->content = ;
	env_pair->next = NULL;
	env_pair->prev = NULL;
	if (!*token)
	{
		*token = env_pair;
		return ;
	}
	temp = get_last_token(token);
	temp->next = env_pair;
	env_pair->prev = temp;
}

//criar uma função que retorna o valor 
// key: tudo antes do =
// content: tudo depois do =
