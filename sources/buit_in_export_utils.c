/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buit_in_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:18:26 by asanni            #+#    #+#             */
/*   Updated: 2024/09/16 20:29:26 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	var_exists(t_mini *minishell)
{
	char	**split;

	while (minishell->token != NULL)
	{
		if (minishell->token->type == EXPORT)
		{
			minishell->token = minishell->token->next;
			if (minishell->token != NULL)
			{
				split = ft_split_two(minishell->token->str, '=');
				if (split != NULL && split[0] != NULL)
				{
					if (return_var(split[0], 0) != NULL)
					{
						free_split(split);
						return (1);
					}
				}
				free_split(split);
			}
		}
		minishell->token = minishell->token->next;
	}
	return (0);
}

void	put_new_value(t_mini *minishell, char *var)
{
	t_env	*current;
	char	**split;

	current = minishell->env_exp;
	split = ft_split_two(var, '=');
	if (!split || !split[0])
	{
		free_matrix(split);
		return ;
	}
	while (current != NULL)
	{
		if (ft_strcmp(current->key, split[0]) == 0)
		{
			free(current->content);
			current->content = ft_strdup(split[1]);
			break ;
		}
		current = current->next;
	}
	free_matrix(split);
}

void	export(t_mini *minishell)
{
	while (minishell->token != NULL)
	{
		if ()//validar se a var é valida
		{
			if (var_exists(minishell->token->str) == 1)
				put_new_value(minishell, minishell->token->str);
			else
				list_env(minishell->env_exp, minishell->token->str);
		}
		minishell->token = minishell->token->next;
	}
}
