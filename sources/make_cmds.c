/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/08/19 19:46:45 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**make_options(t_token **token)
{
	char	**options;
	char	**opt_bckp;
	int		len;

	len = 0;
	if (search_options(*token))
		return (NULL);
	len = return_len(*token);
	options = ft_calloc(sizeof(char *), (len + 1));
	opt_bckp = options;
	while (*token != NULL && (*token)->type != PIPE)
	{
		if (find_redir(*token) == 1)
			*token = (*token)->next;
		else
			(*options++) = ft_strdup((*token)->str);
		*token = (*token)->next;
	}
	return (opt_bckp);
}

t_cmd	*get_last_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	make_one_cmd(t_cmd **cmd, t_token **token, t_mini *minishell)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;
	//int		i;

	//i = 0; (variavel não usada)
	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return ;
	new_cmd->str = (*token)->str;
	new_cmd->options = make_options(token);
	new_cmd->path = verify_path(minishell, new_cmd->str);
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = get_last_cmd(cmd);
	temp->next = new_cmd;
	new_cmd->prev = temp;
}

void	make_cmds(t_cmd **cmd, t_token **token, t_mini *minishell)
{
	if (cmd == NULL || token == NULL || *token == NULL)
		return ;
	while (*token != NULL)
	{
		make_one_cmd(cmd, token, minishell);
		while (*token != NULL && (*token)->type != PIPE)
		{
			if (find_redir(*token) == 1)
				*token = (*token)->next;
			else
				*token = (*token)->next;
		}
		if (*token != NULL && (*token)->type == PIPE)
			*token = (*token)->next;
	}
}

// gerenciar error de malloc
