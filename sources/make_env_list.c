/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:27:26 by asanni            #+#    #+#             */
/*   Updated: 2024/08/17 16:31:56 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*get_last_env(t_env **token)
{
	t_env	*temp;

	temp = *token;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	list_env(t_env **env, char *split)
{
	t_env	*env_pair;
	t_env	*temp;
	char	**env_split;

	env_pair = malloc(sizeof(t_env));
	env_split = ft_split_two(split, '=');
	if (env_pair == NULL)
		return ;
	env_pair->key = env_split[0];
	env_pair->content = env_split[1];
	env_pair->next = NULL;
	env_pair->prev = NULL;
	free(split);
	if (!*env)
	{
		*env = env_pair;
		return ;
	}
	temp = get_last_env(env);
	temp->next = env_pair;
	env_pair->prev = temp;
}

void	make_env_list(t_mini *minishell)
{
	int	i;

	i = 0;
	while (minishell->env_content[i] != NULL)
	{
		list_env(&minishell->env_exp, minishell->env_content[i]);
		i++;
	}
	free_matrix(minishell->env_content);
}
