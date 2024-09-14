/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/14 13:49:05 by asanni           ###   ########.fr       */
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

int	expand_variable(t_mini *minishell, t_aux *aux)
{
	char	*var_key;
	char	*var_value;

	var_key = return_var(&aux->token[*aux->i + 1]);
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

char	*expand_token(t_mini *minishell, t_aux *aux)
{
	int		i;
	int		j;

	aux->result = ft_calloc(1, calculate_size(minishell, aux->token));
	i = 0;
	j = 0;
	aux->i = &i;
	aux->j = &j;
	if (!aux->result)
		return (NULL);
	while (aux->token[i])
	{
		if (aux->token[i] == '$')
		{
			if (is_variable_expandable(aux->token, i + 1))
				expand_variable(minishell, aux);
			else
			{
				aux->result[j++] = '$';
				i++;
			}
		}
		else
			aux->result[j++] = aux->token[i++];
	}
	return (aux->result);
}
