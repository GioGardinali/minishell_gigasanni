/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/02 20:21:32 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//quero que esta função percorra a token list 
//ache as var para expandir em todos os casos 
//ignore casos que não serão expandidos
//cuidado com as aspas

void	expand_var(t_mini *minishell)
{
	char	str;
	int		i;

	i = 0;
	while (minishell->token != NULL)
	{
		str = minishell->token->str;
		while (minishell->token->type == WORD || minishell->token->type == VAR)
		{
			while (minishell->token->str[i] '\0')
			{
				
			}
		}
	}
}
