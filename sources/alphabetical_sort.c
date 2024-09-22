/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alphabetical_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:29:45 by asanni            #+#    #+#             */
/*   Updated: 2024/09/22 17:32:53 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdlib.h>

int	compare_keys(char *key1, char *key2)
{
	return (ft_strcmp(key1, key2));
}

void	insert_sorted(t_env **sorted, t_env *node)
{
	t_env	*temp;

	temp = *sorted;
	if (!temp || compare_keys(node->key, temp->key) < 0)
	{
		node->next = temp;
		if (temp)
			temp->prev = node;
		*sorted = node;
		return ;
	}
	while (temp->next && compare_keys(temp->next->key, node->key) < 0)
	{
		temp = temp->next;
	}
	node->next = temp->next;
	if (temp->next)
		temp->next->prev = node;
	temp->next = node;
	node->prev = temp;
}

void	sort_env_list(t_env **env)
{
	t_env	*sorted;
	t_env	*current;
	t_env	*next;

	sorted = NULL;
	current = *env;
	while (current)
	{
		next = current->next;
		current->prev = NULL;
		current->next = NULL;
		insert_sorted(&sorted, current);
		current = next;
	}
	*env = sorted;
}
