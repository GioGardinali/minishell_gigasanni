/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/25 19:58:23 by gigardin         ###   ########.fr       */
=======
/*   Updated: 2024/09/25 19:51:51 by asanni           ###   ########.fr       */
>>>>>>> 9021295b26141e9f977f88ce08d258220a673d98
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
