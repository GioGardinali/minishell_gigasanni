/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:03:25 by asanni            #+#    #+#             */
/*   Updated: 2024/09/21 16:49:01 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_redir(t_token *token)
{
	return ((token->type == APPEND) || (token->type == TRUNC)
				|| (token->type == INPUT));
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

t_cmd	*get_last_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
