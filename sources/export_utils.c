/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:18:26 by asanni            #+#    #+#             */
/*   Updated: 2024/10/07 19:41:05 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_var_name(char *str)
{
	char	**split;
	int		i;

	if (str[0] == '?')
		return (0);
	split = ft_split_two(str, '=');
	if (split != NULL && split[0][0] != '\0')
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
	else
		return (0);
	free_matrix(split);
	return (0);
}

static int	var_exists(t_mini *minishell, char *str)
{
	t_env	*current;
	char	**split;

	current = minishell->env_exp;
	split = ft_split_two(str, '=');
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

static void	put_new_value(t_mini *minishell, char *var)
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

int	export_options(t_mini *minishell, t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->options[i] != NULL)
	{
		if (valid_var_name(cmd->options[i]) == 1)
		{
			if (var_exists(minishell, cmd->options[i]) == 1)
				put_new_value(minishell, cmd->options[i]);
			else
				list_env(&minishell->env_exp, cmd->options[i]);
		}
		else
		{
			print_error(cmd->options[i], ": is not a valid option");
			status = 1;
		}
		i++;
	}
	return (status);
}

int	print_export(t_mini *minishell)
{
	t_env	*current;

	current = minishell->env_exp;
	sort_env_list(&minishell->env_exp);
	current = current->next;
	while (current != NULL)
	{
		if (current->content != NULL)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->content);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
	return (0);
}
