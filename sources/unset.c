/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:58:15 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 21:25:08 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_env(t_env **env, char *key)
{
	t_env	*current;
	t_env	*remove;

	if (!env || !*env || !key)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			remove = current;
			if (remove == *env)
				*env = remove->next;
			if (remove->prev)
				remove->prev->next = remove->next;
			if (remove->next)
				remove->next->prev = remove->prev;
			free(remove->key);
			if (remove->content)
				free(remove->content);
			free(remove);
			return ;
		}
		current = current->next;
	}
}

int	exclude_valid_var_name(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (!is_valid(name[i], i))
			return (0);
		i++;
	}
	return (1);
}

int	execute_unset(t_mini *minishell, t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->options[i] != NULL)
	{
		if (exclude_valid_var_name(cmd->options[i]) == 1)
			unset_env(&minishell->env_exp, cmd->options[i]);
		else
		{
			print_error(cmd->options[i], ": is not a valid option");
			status = 1;
		}
		i++;
	}
	return (status);
}
