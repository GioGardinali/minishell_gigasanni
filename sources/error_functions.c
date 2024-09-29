/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:12 by asanni            #+#    #+#             */
/*   Updated: 2024/09/29 03:18:25 by asanni           ###   ########.fr       */
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

static void	copy_to_buffer(char *buffer, const char *str, int *index)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		buffer[*index] = str[i];
		i++;
		(*index)++;
	}
}

void	print_error(char *var, char *msg)
{
	int		var_len;
	int		msg_len;
	int		index;
	char	*buffer;

	var_len = ft_strlen(var);
	msg_len = ft_strlen(msg);
	index = 0;
	buffer = malloc(var_len + msg_len + 3);
	if (!buffer)
		return ;
	copy_to_buffer(buffer, var, &index);
	buffer[index++] = ' ';
	copy_to_buffer(buffer, msg, &index);
	buffer[index++] = '\n';
	buffer[index] = '\0';
	write(2, buffer, index);
	free(buffer);
}
