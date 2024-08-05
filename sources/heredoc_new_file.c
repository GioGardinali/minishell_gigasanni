/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_new_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:11:35 by gigardin          #+#    #+#             */
/*   Updated: 2024/08/03 10:19:53 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file_heredoc 	*get_last_file(t_file_heredoc *array_file)
{
	while (array_file->next)
		array_file = array_file->next;
	return (array_file);
}

void	add_file(t_file_heredoc *new_file, t_file_heredoc **array_file)
{
	if (!new_file)
		return ;
	if (!*array_file)
		*array_file = new_file;
	else
		get_last_file(*array_file)->next = new_file;
}