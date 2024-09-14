/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/13 20:28:38 by asanni           ###   ########.fr       */
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

int	expand_variable(t_mini *minishell, char *result, int *i, int *j)
{
	char	*var_key;
	char	*var_value;

	var_key = return_var(&minishell->token->str[*i + 1]);
	if (!var_key)
	{
		result[(*j)++] = '$';
		(*i)++;
		return (1);
	}
	printf("var Key: %s\n", var_key);
	var_value = return_key_content(minishell, var_key);
	if (var_value)
	{
		printf("var: %s\n", var_value);
		append_to_result(result, var_value, j);
	}
	*i += strlen(var_key) + 1;
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

char	*expand_token(t_mini *minishell, char *token)
{
	char	*result;
	int		i;
	int		j;

	result = ft_calloc(sizeof(char), calculate_size(minishell, token));
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '$')
		{
			if (is_variable_expandable(token, i + 1))
			{
				expand_variable(minishell, result, &i, &j);
				printf("exp var\n");
			}
			else
			{
				result[j++] = '$';
				i++;
			}
		}
		else
			result[j++] = token[i++];
	}
	printf ("len: %d\n", calculate_size(minishell, token));
	printf("str: %zu\n", ft_strlen(result));
	return (result);
}
