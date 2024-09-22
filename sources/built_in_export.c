/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:18:36 by asanni            #+#    #+#             */
/*   Updated: 2024/09/14 14:27:50 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_mini *minishell)
{
	while (minishell->env_exp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", minishell->env_exp->key,
			minishell->env_exp->content);
		minishell->env_exp = minishell->env_exp->next;
	}
}
