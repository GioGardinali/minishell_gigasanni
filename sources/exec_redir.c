/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:24 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/13 20:21:52 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void apply_redirections(t_redir *redirs)
{
	int fd;

	while (redirs)
	{
		if (redirs->type == INPUT)
		{
			fd = open(redirs->file, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				return;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == TRUNC)
		{
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				return;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == APPEND)
		{
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				return;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
}

// void execute_cmd_redir(t_cmd *cmd, char **env_content)
// {
// 	apply_redirections(cmd->redirs);
// 	execve(cmd->path, cmd->options, env_content);
// 	perror("execve");
// }

// void execute_cmds_redir(t_cmd *cmd, char **env_content)
// {
// 	pid_t pid;
// 	int status;

// 	while (cmd)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			execute_cmd_redir(cmd, env_content);
// 			exit(EXIT_FAILURE);
// 		}
// 		else if (pid < 0)
// 		{
// 			perror("fork");
// 			return;
// 		}
// 		else
// 		{
// 			waitpid(pid, &status, 0);
// 		}
// 		cmd = cmd->next;
// 	}
// }
