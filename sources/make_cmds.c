/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/10/01 20:28:42 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	identify_type_cmd(t_token **token, t_cmd **cmd, char ***options,
	unsigned int *count_cmd)
{
	t_token	*temp_save;

	if (find_redir(*token) == 1)
	{
		temp_save = *token;
		handle_redirection(token, cmd);
		*token = temp_save;
		if ((*token)->type == HERE_DOC)
			handle_heredoc(token, count_cmd, cmd);
		else
			*token = (*token)->next;
	}
	else
	{
		**options = ft_strdup((*token)->str);
		(*options)++;
		*token = (*token)->next;
	}
}

static char	**make_options(t_token **token, t_cmd **cmd,
	unsigned int *count_cmd)
{
	char	**options;
	char	**opt_bckp;
	int		len;

	len = 0;
	if (search_options(*token))
		return (NULL);
	len = return_len(*token);
	options = ft_calloc(sizeof(char *), (len + 2));
	(*cmd)->options = options;
	opt_bckp = options;
	while (*token != NULL && (*token)->type != PIPE)
		identify_type_cmd(token, cmd, &options, count_cmd);
	return (opt_bckp);
}

void	make_one_cmd(t_cmd **cmd, t_token **token, t_mini *minishell,
	unsigned int *count_cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;
	char	**split;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (new_cmd == NULL)
		return ;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	if (!*cmd)
	{
		*cmd = new_cmd;
	}
	else
	{
		temp = get_last_cmd(cmd);
		temp->next = new_cmd;
		new_cmd->prev = temp;
	}
	split = ft_split((*token)->str, ' ');
	new_cmd->str = ft_strdup(split [0]);
	free_matrix(split);
	if (*cmd == new_cmd)
		new_cmd->heredocs = init_heredoc(minishell);
	else
		new_cmd->heredocs = new_cmd->prev->heredocs;
	new_cmd->options = make_options(token, &new_cmd, count_cmd);
	new_cmd->path = verify_path(minishell, new_cmd->str);
}

void	make_cmds(t_cmd **cmd, t_token **token, t_mini *minishell)
{
	unsigned int	count_cmd;

	count_cmd = 0;
	while (*token != NULL)
	{
		make_one_cmd(cmd, token, minishell, &count_cmd);
		if (*token != NULL && (*token)->type == PIPE)
		{
			*token = (*token)->next;
			count_cmd++;
		}
	}
}
