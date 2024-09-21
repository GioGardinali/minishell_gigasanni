/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:18:26 by asanni            #+#    #+#             */
/*   Updated: 2024/09/21 10:22:00 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_var_name(char *str)
{
	char	**split;
	int		i;

	split = ft_split_two(str, '=');
	if (split != NULL && split[0] != NULL)
	{
		i = 0;
		while (split[0][i] != '\0')
		{
			if (!is_valid(split[0][i], i))
			{
				free_matrix(split);
				return (0);
			}
			i++;
		}
		free_matrix(split);
		return (1);
	}
	free_matrix(split);
	return (0);
}

int	var_exists(t_mini *minishell, t_cmd *cmd)
{
	t_env	*current;
	char	**split;

	current = minishell->env_exp;
	split = ft_split_two(cmd->options[1], '=');
	if (!split || !split[0])
	{
		free_matrix(split);
		return (0);
	}
	while (current != NULL)
	{
		if (ft_strcmp(current->key, split[0]) == 0)
		{
			free_matrix(split);
			return (1);
		}
		current = current->next;
	}
	free_matrix(split);
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

void	export_options(t_mini *minishell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->options[i] != NULL)
	{
		if (valid_var_name(cmd->options[i]) == 1)
		{
			if (var_exists(minishell, cmd) == 1)
				put_new_value(minishell, cmd->str);
			else
				list_env(&minishell->env_exp, cmd->str);
		}
		i++;
	}
}

void	print_export(t_mini *minishell)
{
	t_env	*current;

	current = minishell->env_exp;
	sort_env_list(&minishell->env_exp);
	while (current != NULL)
	{
		if (current->content != NULL)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->content);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
}
