/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:19:07 by asanni            #+#    #+#             */
/*   Updated: 2024/10/08 20:19:25 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*verify_path(t_mini *minishell, char *str)
{
	char	*path_line;
	char	*path;

	if (ft_strchr(str, '/') != NULL || str == NULL)
		return (ft_strdup(str));
	fill_env_content(minishell);
	path_line = search_path(minishell->env_content, "PATH");
	if (!path_line)
	{
		free_matrix(minishell->env_content);
		minishell->env_content = NULL;
		return (NULL);
	}
	path = return_path(path_line, str);
	free_matrix(minishell->env_content);
	minishell->env_content = NULL;
	return (path);
}
