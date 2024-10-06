/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:24 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/06 19:14:43 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	apply_redirection(int type, char *file)
{
	int		fd;

	fd = 0;
	if (type == INPUT || type == HERE_DOC)
		fd = open(file, O_RDONLY);
	else if (type == TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		return (FAIL);
	}
	if (type == INPUT || type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (apply_redirection(redirs->type, redirs->file) == FAIL)
			return (FAIL);
		redirs = redirs->next;
	}
	return (SUCCESS);
}
