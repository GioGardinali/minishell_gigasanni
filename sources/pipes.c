/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:48:38 by asanni            #+#    #+#             */
/*   Updated: 2024/08/06 16:45:21 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_mult_cmds(t_mini minishell);

void	process_two_cmds(t_mini minishell)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(minishell.cmd->path, minishell.cmd->options, __environ);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == -1)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve(minishell.cmd->next->path, minishell.cmd->next->options,
			__environ);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

// void	two_process_cont(char *path, char *options, char **env, int fd)
// {
// 	int	fds[2];

// 	dup2(fds[0], fd);
// 	close(fds[1]);
// 	close(fds[0]);
// 	execve(path, options, env);
// 	exit(EXIT_FAILURE);
// }

/*
teste


void execute_command(t_cmd *cmd, int input_fd, int output_fd)
{
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
	execve(cmd->path, cmd->options, __environ);
	exit(EXIT_FAILURE);
}

pid_t fork_and_execute(t_cmd *cmd, int input_fd, int output_fd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_command(cmd, input_fd, output_fd);
	return pid;
}

void create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
}

void close_unused_fds(int input_fd, int *fd)
{
	if (input_fd != -1)
		close(input_fd);
	if (fd != NULL)
	{
		close(fd[1]);
		input_fd = fd[0];
	}
}

void process_multiple_cmds(t_mini minishell)
{
	int fd[2];
	int prev_fd;
	pid_t pid;
	t_cmd *current_cmd;

	prev_fd = -1;
	current_cmd = minishell.cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
			create_pipe(fd);
		if (current_cmd->next == NULL)
			pid = fork_and_execute(current_cmd, prev_fd, -1);
		else
			pid = fork_and_execute(current_cmd, prev_fd, fd[1]);
		if (current_cmd->next != NULL)
			close_unused_fds(prev_fd, fd);
		else
			close_unused_fds(prev_fd, NULL);
		prev_fd = current_cmd->next != NULL ? fd[0] : -1;
		current_cmd = current_cmd->next;
	}
	while (wait(NULL) > 0);
}

*/