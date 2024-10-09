/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:18:26 by asanni            #+#    #+#             */
/*   Updated: 2024/10/09 19:10:41 by gigardin         ###   ########.fr       */
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

void	put_new_value(t_mini *minishell, char *var)
{
	t_env	*current;
	char	**split;

	current = minishell->env_exp;
	split = ft_split_two(var, '=');
	if (!split || !split[0] || !split[1])
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

t_env	*duplicate_env(t_env *env_exp)
{
	t_env	*start;
	char	var[10000];

	start = NULL;
	while (env_exp)
	{
		ft_memmove(var, env_exp->key, ft_strlen(env_exp->key) + 1);
		if (env_exp->content)
		{
			ft_memmove(&var[ft_strlen(var)], "=", 2);
			ft_memmove(&var[ft_strlen(var)], env_exp->content,
				ft_strlen(env_exp->content) + 1);
		}
		list_env(&start, var);
		env_exp = env_exp->next;
	}
	return (start);
}
