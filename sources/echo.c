/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:47:40 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 20:44:53 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->options[i] != NULL)
	{
		printf("%s", cmd->options[i]);
		if (cmd->options[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	echo_nl(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->options[i] != NULL && ft_strcmp(cmd->options[i], "-n") == 0)
		i++;
	while (cmd->options[i] != NULL)
	{
		printf("%s", cmd->options[i]);
		if (cmd->options[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	execute_echo(t_cmd *cmd)
{
	if (cmd->options[1] != NULL && ft_strcmp(cmd->options[1], "-n") == 0)
		echo_nl(cmd);
	else
		echo(cmd);
	return (0);
}
