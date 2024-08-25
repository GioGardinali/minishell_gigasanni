/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:48:38 by asanni            #+#    #+#             */
/*   Updated: 2024/08/25 17:19:57 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(t_mini minishell, int input_fd, int output_fd)
{
	char	*path;
	char	**options;

	path = minishell.cmd->path;
	options = minishell.cmd->options;
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != -1)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	free_token(&minishell.token);
	free_cmds(&minishell.cmd);
	free(minishell.input);
	free(minishell.env_content);
	if (path != NULL)
		execve(path, options, __environ);
	exit(EXIT_FAILURE);
}

pid_t	fork_and_execute(t_mini minishell, int input_fd, int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_command(minishell, input_fd, output_fd);
	return (pid);
}

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
}

void	close_unused_fds(int input_fd, int *fd)
{
	if (input_fd != -1)
		close(input_fd);
	if (fd != NULL)
	{
		close(fd[1]);
		input_fd = fd[0];
	}
}

void	process_multiple_cmds(t_mini minishell, int prev_fd)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*current_cmd;

	current_cmd = minishell.cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
			create_pipe(fd);
		if (current_cmd->next == NULL)
			pid = fork_and_execute(minishell, prev_fd, -1);
		else
			pid = fork_and_execute(minishell, prev_fd, fd[1]);
		if (current_cmd->next != NULL)
			close_unused_fds(prev_fd, fd);
		else
			close_unused_fds(prev_fd, NULL);
		if (current_cmd->next != NULL)
			prev_fd = fd[0];
		else
			prev_fd = -1;
		current_cmd = current_cmd->next;
	}
	while (wait(NULL) > 0)
		;
}