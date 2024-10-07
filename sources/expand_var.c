/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/10/07 19:40:29 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_vars(t_mini *minishell, t_aux *aux, t_ints *ints )
{
	aux->result = ft_calloc(1, (calculate_size(minishell, aux->token) + 1));
	ints->i = -1;
	ints->j = 0;
	ints->double_q = 0;
	ints->single_q = 0;
	aux->j = &ints->j;
	aux->i = &ints->i;
}

char	*expand_token(t_mini *minishell, t_aux *aux, int quotes)
{
	t_ints	ints;

	init_vars (minishell, aux, &ints);
	if (!aux->result)
		return (NULL);
	while (aux->token[++ints.i])
	{
		if (quotes == 0 && aux->token[ints.i] == '\'' && !ints.double_q)
			ints.single_q = !ints.single_q;
		else if (quotes == 0 && aux->token[ints.i] == '"' && !ints.single_q)
			ints.double_q = !ints.double_q;
		else if (aux->token[ints.i] == '$' && !ints.single_q)
		{
			if (is_variable_expandable(aux->token, ints.i + 1, quotes))
			{
				expand_variable(minishell, aux);
				ints.i--;
			}
			else
				aux->result[ints.j++] = '$';
		}
		else
			aux->result[ints.j++] = aux->token[ints.i];
	}
	return (aux->result);
}

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
