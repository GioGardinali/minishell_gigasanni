/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:12 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 22:48:50 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	print_error(char *var, char *msg)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		write(2, &var[i], 1);
		i++;
	}
	write(2, " ", 1);
	i = 0;
	while (msg[i] != '\0')
	{
		write(2, &msg[i], 1);
		i++;
	}
	write(2, "\n", 1);
}
