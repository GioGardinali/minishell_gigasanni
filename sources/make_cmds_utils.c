/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:03:25 by asanni            #+#    #+#             */
/*   Updated: 2024/10/07 15:49:21 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_redir(t_token *token)
{
	return ((token->type == APPEND) || (token->type == TRUNC)
		|| (token->type == INPUT) || (token->type == HERE_DOC));
}

int	search_options(t_token *token)
{
	return (token == NULL || token->str == NULL
		|| token->type == PIPE);
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

void	last_cmd(t_cmd *temp, t_cmd **cmd, t_cmd *new_cmd)
{
		temp = get_last_cmd(cmd);
		temp->next = new_cmd;
		new_cmd->prev = temp;
}
