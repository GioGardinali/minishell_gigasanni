/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:31:39 by asanni            #+#    #+#             */
/*   Updated: 2024/09/13 20:09:45 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid(char c, int position)
{
	if (position == 0)
	{
		if (!ft_isalpha(c) && c != '_')
			return (0);
	}
	else
	{
		if (!(ft_isalpha(c) || ft_isdigit(c) || c == '_'))
			return (0);
	}
	return (1);
}

int	var_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0' && is_valid(str[i], len))
	{
		len++;
		i++;
	}
	return (len);
}

char	*return_var(char *str)
{
	char	*var;
	int		len;
	int		i;
	int		j;

	len = var_len(str);
	if (len == 0)
		return (NULL);
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0' && is_valid(str[i], j + 1))
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = '\0';
	return (var);
}

char	*return_key_content(t_mini *minishell, char *var_key)
{
	t_env	*current;

	current = minishell->env_exp;
	if (!var_key)
		return (NULL);
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var_key) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	add_variable_size(t_mini *minishell, char *token, int *i)
{
	char	*var_key;
	char	*var_value;
	int		size;

	var_key = return_var(&token[*i + 1]);
	size = 0;
	if (var_key)
	{
		var_value = return_key_content(minishell, var_key);
		if (var_value)
			size = ft_strlen(var_value);
		*i += ft_strlen(var_key) + 1;
		free(var_key);
	}
	else
	{
		size = 1;
		(*i)++;
	}
	return (size);
}
