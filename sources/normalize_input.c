/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 17:42:31 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	norme(t_mini *minishell, t_token *token)
{
	int			i;
	char		*input;
	char		**split;

	i = 0;
	if (check_input(minishell->input))
		return ;
	if (!(minishell->input[0] != '\0'))
		return ;
	input = adjust_spaces(minishell->input);
	split = ft_split(input, -1);
	while (split[i] != NULL)
		make_tokens(&minishell->token, split[i++]);
	expand_all_tokens(minishell);
	free_matrix(split);
	token = minishell->token;
	while (token != NULL)
	{
		make_cmds(&minishell->cmd, &token, minishell);
		if (token != NULL)
			token = token->next;
	}
	free(input);
}
