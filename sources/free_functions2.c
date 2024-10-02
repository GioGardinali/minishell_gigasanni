/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:01:07 by asanni            #+#    #+#             */
/*   Updated: 2024/10/02 20:02:48 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_minishell(t_mini *minishell)
{
	if (minishell->cmd != NULL)
	{
		clean_heredoc_files(minishell->cmd);
		free_cmds(&minishell->cmd);
	}
	if (minishell->token != NULL)
		free_token(&minishell->token);
	free_cmds(&minishell->cmd);
	minishell->token = NULL;
	close(minishell->std_in);
	close(minishell->std_out);
}

void	free_token_bc(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp != NULL)
	{
		temp = (*token)->prev;
		free((*token)->str);
		free(*token);
		(*token) = temp;
	}
	token = NULL;
}
