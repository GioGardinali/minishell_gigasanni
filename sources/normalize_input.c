/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/09/22 20:00:25 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
esta função pega o input e faz todos os tratamentos que ele precisa
ela checa o prompt da readline
lida com os espaços da split
e cria os tokens com o resultado da split
tenho que arrumar a parte que lida com os cmds para passar para a execv
provavelmente melhor lidar com isso em outra função
*/

void	expand_all_tokens(t_mini *minishell)
{
	t_token	*current;
	t_aux	aux;

	current = minishell->token;
	while (current != NULL)
	{
		aux.token = current->str;
		current->str = expand_token(minishell, &aux);
		current = current->next;
	}
}

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
	token = minishell->token;
	while (token != NULL)
	{
		make_cmds(&minishell->cmd, &token, minishell);
		if (token != NULL)
			token = token->next;
		//print_cmds(minishell->cmd);
	}
	free_matrix(split);
	free(input);
}
