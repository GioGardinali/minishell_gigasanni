/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:03:25 by asanni            #+#    #+#             */
/*   Updated: 2024/07/22 20:10:35 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_redir(t_token *token)
{
	return ((token->type == APPEND) || (token->type == HERE_DOC)
		|| (token->type == TRUNC) || (token->type == INPUT));
}

int	search_options(t_token *token)
{
	return (token == NULL || token->str == NULL
		|| (ft_strcmp(token->str, "|") == 0));
}

int	return_len(t_token *token)
{
	int	len;

	len = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (find_redir(token) == 1)
			token = token->next;
		else
			len++;
		token = token->next;
	}
	return (len);
}

void	print_matrix(char **matrix)
{
	if (matrix == NULL)
		return ;
	for (int i = 0; matrix[i]; i++)
	{
		printf("%s\n", matrix[i]);
	}
}
