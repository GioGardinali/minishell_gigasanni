/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:42:06 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/01 20:47:54 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	handle_redirection(t_token **token, t_cmd **cmd)
{
	int	type;

	type = (*token)->type;
	*token = (*token)->next;
	if (*token != NULL)
		add_redir(&(*cmd)->redirs, type, (*token)->str);
	*token = (*token)->next;
}

void	handle_heredoc(t_token **token, unsigned int *count_cmd, t_cmd **cmd)
{
	if (!execute_heredoc((*token)->next->str, *count_cmd,
			(*cmd)->heredocs, (*token)->prev == NULL))
	{
		ft_putendl_fd("Heredoc error", 2);
		exit(EXIT_FAILURE);
	}
	*token = (*token)->next->next;
}
