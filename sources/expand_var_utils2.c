/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:31:39 by asanni            #+#    #+#             */
/*   Updated: 2024/09/24 19:47:29 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	calculate_size(t_mini *minishell, char *token)
{
	int	total_size;
	int	i;

	total_size = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_valid(token[i + 1], 0))
			total_size += add_variable_size(minishell, token, &i);
		else
		{
			total_size++;
			i++;
		}
	}
	return (total_size);
}

void	append_to_result(char *result, char *str, int *j)
{
	int	len;

	len = ft_strlen(str);
	ft_strcpy(&result[*j], str);
	*j += len;
}

char	*get_env_value(t_env *env_list, const char *key)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	expand_variable(t_mini *minishell, t_aux *aux)
{
	char	*var_key;
	char	*var_value;

	var_key = return_var(&aux->token[*aux->i + 1], 1);
	if (!var_key)
	{
		aux->result[(*aux->j)++] = '$';
		(*aux->i)++;
		return (1);
	}
	var_value = return_key_content(minishell, var_key);
	if (var_value)
		append_to_result(aux->result, var_value, aux->j);
	*aux->i += strlen(var_key) + 1;
	free(var_key);
	return (1);
}

int	is_variable_expandable(char *token, int pos)
{
	int		i;
	int		in_double_quotes;
	int		in_single_quotes;

	i = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while (i < pos)
	{
		if (token[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (token[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		i++;
	}
	if (in_single_quotes)
		return (0);
	return (1);
}
