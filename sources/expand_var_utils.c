/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:31:39 by asanni            #+#    #+#             */
/*   Updated: 2024/09/10 19:02:33 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid(char c, int position)
{
	if (position == 1)
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
	if (str[i] == '$')
		i++;
	while (str[i] != '\0' && is_valid(str[i], len + 1))
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
	i = 1;
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
