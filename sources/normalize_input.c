/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/10/05 13:53:31 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	norme(t_mini *minishell, t_token *token)
{
	int		i;
	char	*input;
	char	**split;

	i = 0;
	if (check_input(minishell->input) != 0)
		return (update_exit_status(minishell, 1));
	if (!(minishell->input[0] != '\0'))
		return (update_exit_status(minishell, 1));
	input = adjust_spaces(minishell->input);
	split = ft_split(input, -1);
	free(input);
	while (split[i] != NULL)
		make_tokens(&minishell->token, split[i++]);
	expand_all_tokens(minishell);
	free_matrix(split);
	token = minishell->token;
	while (token != NULL)
	{
		make_cmds(&minishell->cmd, &token, minishell);
		//print_cmds(minishell->cmd);
		if (token != NULL)
			token = token->next;
	}
	return (0);
}
