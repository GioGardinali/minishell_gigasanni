/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:01:07 by asanni            #+#    #+#             */
/*   Updated: 2024/10/05 16:56:16 by gigardin         ###   ########.fr       */
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

void	clean_exec_comand(t_mini *minishell)
{
	quita_esses_heredocs(minishell->cmd->heredocs);
	free(minishell->pids);
	free(minishell->env_content);
	free(minishell->input);
	free_cmds(&minishell->cmd);
	free_env(&minishell->env_exp);
	free_token(&minishell->token);
	close(minishell->std_in);
	close(minishell->std_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
