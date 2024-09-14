/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/11 20:08:47 by gigardin         ###   ########.fr       */
=======
/*   Updated: 2024/09/13 19:59:29 by asanni           ###   ########.fr       */
>>>>>>> 7f638b65e978b78f4725ff2d227eb67019874424
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
<<<<<<< HEAD
	//printf("%s\n", expand_token(minishell, minishell->token->str));
=======
>>>>>>> 7f638b65e978b78f4725ff2d227eb67019874424
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
