/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:49:58 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/27 19:29:36 by asanni           ###   ########.fr       */
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
