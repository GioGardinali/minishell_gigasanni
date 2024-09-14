/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/09/13 22:49:52 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdbool.h>

/*
esta função pega o input e faz todos os tratamentos que ele precisa
ela checa o prompt da readline
lida com os espaços da split
e cria os tokens com o resultado da split
tenho que arrumar a parte que lida com os cmds para passar para a execv
provavelmente melhor lidar com isso em outra função
*/

// void	norme(t_mini *minishell, t_token *token)
// {
// 	int			i;
// 	char		*input;
// 	char		**split;

// 	i = 0;
// 	if (check_input(minishell->input))
// 		return ;
// 	if (!(minishell->input[0] != '\0'))
// 		return ;
// 	input = adjust_spaces(minishell->input);
// 	split = ft_split(input, -1);
// 	while (split[i] != NULL)
// 		make_tokens(&minishell->token, split[i++]);
// 	token = minishell->token;
// 	printf("%s\n", expand_token(minishell, minishell->token->str));
// 	while (token != NULL)
// 	{
// 		make_cmds(&minishell->cmd, &token, minishell);
// 		if (token != NULL)
// 			token = token->next;
// 	}
// 	free_matrix(split);
// 	free(input);
// }

void	expand_all_tokens(t_mini *minishell)
{
	t_token	*current;

	current = minishell->token;
	while (current != NULL)
	{
		current->str = expand_token(minishell, current->str);
		printf ("aqui\n");
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
	//printf("%s\n", expand_token(minishell, minishell->token->str));
	while (token != NULL)
	{
		make_cmds(&minishell->cmd, &token, minishell);
		if (token != NULL)
			token = token->next;
	}
	free_matrix(split);
	free(input);
}

// void	teste(t_mini *minishell)
// {
// 	while (minishell.token != NULL)
// 	{
// 		expand_token(minishell.token->str)
// 	}
// }
