/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:48:38 by asanni            #+#    #+#             */
/*   Updated: 2024/09/01 17:20:45 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(t_mini minishell, int input_fd, int out_fd, t_cmd cmd)
{
	char	*path;
	char	**options;

	path = cmd.path;
	options = cmd.options;
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	free_token(&minishell.token);
	free(minishell.input);
	if (path != NULL)
		execve(path, options, __environ);
	exit(EXIT_FAILURE);
}

pid_t	fork_and_execute(
	t_mini minishell, int input_fd, int out_fd, t_cmd cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_command(minishell, input_fd, out_fd, cmd);
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
	// pid_t	pid;
	t_cmd	*current_cmd;

	current_cmd = minishell.cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
			create_pipe(fd);
		if (current_cmd->next == NULL)
			//pid = fork_and_execute(minishell, prev_fd, -1, *current_cmd);
		fork_and_execute(minishell, prev_fd, -1, *current_cmd);
		else
			//pid = fork_and_execute(minishell, prev_fd, fd[1], *current_cmd);
		fork_and_execute(minishell, prev_fd, fd[1], *current_cmd);
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
