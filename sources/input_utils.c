/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/14 15:51:00 by asanni           ###   ########.fr       */
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

char	*normalize_input(t_mini *minishell)
{
	char	*input;
	char	**tokens;
	char	*cmd;
	int		i;

	check_input(minishell->input);
	input = adjust_spaces(minishell->input);
	i = 0;
	while (tokens[i] != NULL)
	{
		cmd = ft_strjoin("/", tokens[i]);
		i++;
	}
	printf("%s", cmd);
	return (cmd);
}

void	norme(t_mini *minishell, t_token *token)
{
	int			i;
	char		*input;
	char		**split;

	i = 0;
	check_input(minishell->input);
	input = adjust_spaces(minishell->input);
	split = ft_split(input, -1);
	while (split[i] != NULL)
	{
		make_tokens(token, split[i]);
		i++;
	}
}
