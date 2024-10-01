/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/10/01 17:07:37 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_token(t_mini *minishell, t_aux *aux, int quotes)
{
	int		i;
	int		j;
	int		in_double_quotes;
	int		in_single_quotes;

	aux->result = ft_calloc(1, (calculate_size(minishell, aux->token) + 1));
	i = 0;
	j = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	aux->i = &i;
	aux->j = &j;
	if (!aux->result)
		return (NULL);
	while (aux->token[i])
	{
		if (quotes == 0 && aux->token[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (quotes == 0 && aux->token[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		else if (aux->token[i] == '$' && !in_single_quotes)
		{
			if (is_variable_expandable(aux->token, i + 1, quotes))
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

// char	*expand_token(t_mini *minishell, t_aux *aux, int quotes)
// {
// 	int	i;
// 	int	j;
// 	int	in_double_quotes;
// 	int	in_single_quotes;

// 	i = 0;
// 	j = 0;
// 	in_double_quotes = 0;
// 	in_single_quotes = 0;
// 	aux->result = ft_calloc(1, (calculate_size(minishell, aux->token) + 1));
// 	if (!aux->result)
// 		return (NULL);
// 	aux->i = &i;
// 	aux->j = &j;
// 	while (aux->token[i])
// 	{
// 		if (!handle_quotes(aux->token, &i, &in_double_quotes,
// 				&in_single_quotes, quotes)
// 			&& !handle_dollar_sign(minishell, aux, quotes, &in_single_quotes))
// 		{
// 			aux->result[j++] = aux->token[i++];
// 		}
// 	}
// 	return (aux->result);
// }

void	expand_all_tokens(t_mini *minishell)
{
	t_token	*current;
	t_aux	aux;

	current = minishell->token;
	while (current != NULL)
	{
		aux.token = current->str;
		current->str = expand_token(minishell, &aux, 0);
		current = current->next;
	}
}
