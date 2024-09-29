/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:10:59 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 20:45:55 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_env(t_mini *minishell)
{
	t_env	*current;

	current = minishell->env_exp->next;
	while (current != NULL)
	{
		if (current->content)
			ft_printf("%s=%s\n", current->key, current->content);
		current = current->next;
	}
	return (0);
}
