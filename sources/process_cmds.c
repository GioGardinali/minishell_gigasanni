/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:24:12 by asanni            #+#    #+#             */
/*   Updated: 2024/10/07 20:19:22 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_command(t_mini minishell, int input_fd, int *out_fd,
	t_cmd *cmd)
{
	char	*path;
	char	**options;

	path = cmd->path;
	options = cmd->options;
	close_std_int_and_out(&minishell);
	if (cmd->prev != NULL || cmd->next != NULL)
		close(out_fd[0]);
	setup_file_descriptors(input_fd, out_fd[1]);
	if (apply_redirections(cmd->redirs) == FAIL)
	{
		if (is_built_in(cmd->str))
			close_fds(out_fd, input_fd);
		clean_exec_comand(&minishell);
		minishell.exit_status = 1;
	}
	else if (is_built_in (cmd->str) != 0)
	{
		close_fds(out_fd, input_fd);
		execute_built_in(&minishell, cmd);
		clean_exec_comand(&minishell);
	}
	else
		execve_function(&minishell, path, options);
	exit(minishell.exit_status);
}

pid_t	fork_and_execute(t_mini *minishell, int input_fd,
	int *out_fd, t_cmd *cmd)
{
	pid_t	pid;

	if (is_built_in(cmd->str) != 0 && out_fd[1] == -1 && cmd->prev == NULL)
	{
		if (apply_redirections(cmd->redirs) == SUCCESS)
			execute_built_in(minishell, cmd);
		else
			minishell->exit_status = 1;
		dup2(minishell->std_in, 0);
		dup2(minishell->std_out, 1);
		close(minishell->std_in);
		close(minishell->std_out);
		return (minishell->exit_status);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_command(*minishell, input_fd, out_fd, cmd);
	return (pid);
}

static void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
}

static void	close_unused_fds(int input_fd, int *fd, t_cmd *cmd)
{
	if (input_fd != -1)
		close(input_fd);
	if (cmd->next != NULL)
	{
		close(fd[1]);
		input_fd = fd[0];
	}
}

void	process_multiple_cmds(t_mini *minishell, int prev_fd)
{
	int			fd[2];
	t_cmd		*current_cmd;
	int			*pids;
	int			i;

	current_cmd = minishell->cmd;
	pids = malloc(sizeof(int) * (count_cmd(minishell->token) + 1));
	i = 0;
	minishell->pids = pids;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
			create_pipe(fd);
		pids[i++] = return_pid(minishell, current_cmd, prev_fd, fd);
		close_unused_fds(prev_fd, fd, current_cmd);
		if (current_cmd->next != NULL)
			prev_fd = fd[0];
		else
			prev_fd = -1;
		current_cmd = current_cmd->next;
	}
	if (is_first_and_builtin(minishell) == 1)
		return ;
	pids[i] = -42;
	wait_and_update_exit_status(minishell, pids);
}
