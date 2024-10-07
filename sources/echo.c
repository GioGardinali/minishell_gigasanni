/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:47:40 by asanni            #+#    #+#             */
/*   Updated: 2024/10/07 19:33:57 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->options[i] != NULL)
	{
		write(1, cmd->options[i], ft_strlen(cmd->options[i]));
		if (cmd->options[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

static void	echo_nl(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->options[i] != NULL && ft_strcmp(cmd->options[i], "-n") == 0)
		i++;
	while (cmd->options[i] != NULL)
	{
		write(1, cmd->options[i], ft_strlen(cmd->options[i]));
		if (cmd->options[i + 1] != NULL)
			write(1, " ", 1);
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
