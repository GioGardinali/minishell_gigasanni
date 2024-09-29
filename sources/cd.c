/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:38:49 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 21:01:41 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_cd(t_mini *minishell)
{
	char	*path;

	path = minishell->cmd->options[1];
	if (minishell->cmd->options[2] != NULL)
		return (1);
	else if (minishell->cmd->options[1] == NULL)
		path = return_key_content(minishell, "HOME");
	if (chdir(path) == -1)
	{
		perror(path);
		return (1);
	}
	return (0);
}
