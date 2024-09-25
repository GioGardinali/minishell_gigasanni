/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:24 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/24 19:41:44 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	apply_redirection(int type, char *file)
{
	int	fd;

	if (type == INPUT)
		fd = open(file, O_RDONLY);
	else if (type == TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return ;
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (type == INPUT)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		apply_redirection(redirs->type, redirs->file);
		redirs = redirs->next;
	}
}
