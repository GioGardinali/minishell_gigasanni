/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:12:09 by asanni            #+#    #+#             */
/*   Updated: 2024/07/02 16:06:21 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*normalize_input(t_mini *minishell)
{
	char	*input;
	char	**cmds;
	char	*cmd;
	int		i;

	input = minishell->input;
	cmds = ft_split(input, ' ');
	i = 0;
	while (cmds[i] != NULL)
	{
		cmd = ft_strjoin("/", cmds[i]);
		i++;
	}
	printf("%s", cmd);
	return (cmd);
}

// int	check_input(char *input)
// {
// 	if (check_quotes(input))
// 		return (-1);
// 	if (check_redirect(input))
// 		return (-1);
// 	if (check_pipes(input))
// 		return (-1);
// 	return (0);
// }

/*
Criar funções para verificar o input da readline
arruma-los e retorná-los certinho para passar
para a execve
*/
