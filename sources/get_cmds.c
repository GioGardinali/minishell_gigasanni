/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/07/20 17:47:30 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_redir(t_token *token)
{
	return ((token->type == APPEND) || (token->type == HERE_DOC)
		|| (token->type == TRUNC) || (token->type == INPUT));
}

static int	search_options(t_token *token)
{
	return (token == NULL || token->str == NULL
		|| (ft_strcmp(token->str, "|") == 0));
}

char	**make_options(t_token *token)
{
	t_token	*temp;
	char	**options;
	int		len;

	len = 0;
	temp = token;
	if (search_options(token))
		return (NULL);
	while (token != NULL && token->type != PIPE)
	{
		if (find_redir(token->type))
			token = token->next->next;
		else
			len++;
	}
	options = malloc(sizeof(char *) * (len + 1));
	while (token != NULL && token->type != PIPE)
	{
		if (find_redir(token->type))
			token = token->next->next;
		else
			*options++ = ft_strdup(temp->str);
	}
	options[len] = NULL;
	return (options);
}

static void	make_cmds(t_cmd **cmd, t_token *token, t_mini *minishell)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return ;
	new_cmd->str = token->str;
	new_cmd->options = make_options(token->next);
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

// gerenciar error de malloc
