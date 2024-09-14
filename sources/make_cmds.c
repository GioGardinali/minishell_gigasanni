/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
/*   Updated: 2024/09/14 00:50:35 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_redir(t_redir **redirs, int type, char *file);

// static void	init_heredoc(t_mini *temp_minishell)
// {
// 	t_heredoc	*heredoc;

// 	heredoc = ft_calloc(sizeof(t_heredoc), 1);
// 	heredoc->size = count_cmd(temp_minishell->token);
// 	heredoc->array = ft_calloc(sizeof(t_file_heredoc *), heredoc->size);
// 	ft_get_shell()->heredocs = heredoc;
// }

static void	identify_type_cmd(t_token **token, t_cmd **cmd, char ***options,
	int *count_cmd)
{
	int	type;

	if (find_redir(*token) == 1)
	{
		type = (*token)->type;
		*token = (*token)->next;
		if (*token != NULL)
			add_redir(&(*cmd)->redirs, type, (*token)->str);
		*token = (*token)->next;
	}
	else if ((*token)->type == HERE_DOC)
	{
		// if (!execute_heredoc((*token)->next->str, &count_cmd, ft_get_shell()->heredocs,
		// 		(*token)->prev == NULL))
		// {
		// 	ft_putendl_fd("Heredoc error", 2);
		// 	exit(EXIT_FAILURE);
		// }
		printf("quantidade de comandos: %d\n", *count_cmd);
		*token = (*token)->next->next;
	}
	else
	{
		**options = ft_strdup((*token)->str);
		(*options)++;
		*token = (*token)->next;
	}
}

static char	**make_options(t_token **token, t_cmd **cmd, int *count_cmd)
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

void	add_redir(t_redir **redirs, int type, char *file)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->next = NULL;
	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	temp = *redirs;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}

void	make_one_cmd(t_cmd **cmd, t_token **token, t_mini *minishell,
	int *count_cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (new_cmd == NULL)
		return ;
	new_cmd->str = (*token)->str;
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
	int	count_cmd;

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
