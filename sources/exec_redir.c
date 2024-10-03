/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:24 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/03 20:30:57 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	apply_redirection(int type, char *file)
{
	int			fd;
	t_mini		*minishell;

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
		minishell = ft_global_mini(NULL);
		free(minishell->pids);
		free(minishell->env_content);
		free(minishell->input);
		clean_heredoc_files(minishell->cmd);
		free_cmds(&minishell->cmd);
		free_env(&minishell->env_exp);
		free_token(&minishell->token);
		close(minishell->std_in);
		close(minishell->std_out);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (type == INPUT || type == HERE_DOC)
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
