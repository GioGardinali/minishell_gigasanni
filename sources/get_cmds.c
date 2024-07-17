/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/07/17 19:57:14 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_cmds(t_cmd **cmd, t_token token)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return ;
	new_cmd->str = token.str;
	new_cmd->options = token.next->str;
	//new_cmd->path = split;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = get_last_token(cmd);
	temp->next = new_cmd;
	new_cmd->prev = temp;
}
