/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:18:36 by asanni            #+#    #+#             */
/*   Updated: 2024/10/09 19:10:49 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_export(t_mini *minishell)
{
	t_env	*current;
	t_env	*start;

	start = duplicate_env(minishell->env_exp);
	current = start;
	sort_env_list(&current);
	current = current->next;
	while (current != NULL)
	{
		if (current->content != NULL)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->content);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
	free_env(&start);
	return (0);
}

int	execute_export(t_mini *minishell, t_cmd *cmd)
{
	if (!cmd->options[1])
		return (print_export(minishell));
	else
		return (export_options(minishell, cmd));
}
