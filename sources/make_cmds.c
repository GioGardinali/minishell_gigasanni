/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/09/26 21:00:10 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	identify_type_cmd(t_token **token, t_cmd **cmd, char ***options,
	unsigned int *count_cmd)
{
	if (find_redir(*token) == 1)
		handle_redirection(token, cmd);
	else if ((*token)->type == HERE_DOC)
	{
		handle_heredoc(token, count_cmd, cmd);
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
	options = ft_calloc(sizeof(char *), (len + 1));
	opt_bckp = options;
	while (*token != NULL && (*token)->type != PIPE)
	{
		identify_type_cmd(token, cmd, &options, count_cmd);
	}
	return (opt_bckp);
}

// Projeto de função 100% experimental
void	make_one_cmd(t_cmd **cmd, t_token **token, t_mini *minishell,
	unsigned int *count_cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;
	char	**split;

	split = ft_split((*token)->str, ' ');
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (new_cmd == NULL)
		return ;
	new_cmd->str = ft_strdup(split [0]);
	free_matrix(split);
	if (!*cmd)
		new_cmd->heredocs = init_heredoc(minishell); // checar para não mallocar em cada comando? if (!*cmd) [usar cmd->prev como base]
	else
		new_cmd->heredocs = (*cmd)->prev->heredocs;
	new_cmd->options = make_options(token, &new_cmd, count_cmd);
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
