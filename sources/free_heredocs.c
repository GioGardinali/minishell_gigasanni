/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:49:58 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/05 17:16:24 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_heredoc_files(t_cmd *cmd)
{
	t_cmd			*current_cmd;
	t_file_heredoc	*next_file;
	t_file_heredoc	*current_file;
	int				i;

	current_cmd = cmd;
	i = 0;
	while (current_cmd->heredocs->array[i])
	{
		current_file = current_cmd->heredocs->array[i];
		while (current_file)
		{
			next_file = current_file->next;
			unlink(current_file->file);
			free(current_file->file);
			free(current_file);
			current_file = next_file;
		}
			i++;
		free(current_cmd->heredocs->array[i]);
	}
	free(current_cmd->heredocs->array);
	free(current_cmd->heredocs);
}

void	clean_fork_heredoc(t_mini *minishell)
{
	free_token_bc(&minishell->token);
	free_token(&minishell->token);
	free_env(&minishell->env_exp);
	free_cmds(&minishell->cmd);
}
