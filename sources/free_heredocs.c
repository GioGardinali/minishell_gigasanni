/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:49:58 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/22 16:51:35 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_heredoc_files(t_cmd *cmd)
{
	t_cmd			*current_cmd;
	t_file_heredoc	*next_file;
	t_file_heredoc	*current_file;

	current_cmd = cmd;
	while (current_cmd)
	{
		if (current_cmd->heredocs)
		{
			current_file = current_cmd->heredocs->array[0];
			while (current_file)
			{
				next_file = current_file->next;
				unlink(current_file->file);
				free(current_file->file);
				free(current_file);
				current_file = next_file;
			}
			free(current_cmd->heredocs->array);
			free(current_cmd->heredocs);
		}
		current_cmd = current_cmd->next;
	}
}
