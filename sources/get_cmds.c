/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/07/20 15:50:20 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_cmds(t_cmd **cmd, t_token token, t_mini *minishell)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return ;
	new_cmd->str = token.str;
	if (ft_strcmp(token.next->str, "|") == 0)
		new_cmd->options = NULL;
	new_cmd->options = token.next->str;
	new_cmd->path = verify_path(minishell, new_cmd->str);
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

void	make_options(t_cmd **cmd, t_token token, t_mini *minishell)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	while (!(ft_strcmp(token.next->str, "|") == 0))
	{
		temp->options[i] = token.next->str;
		i++;
	}
	
}
