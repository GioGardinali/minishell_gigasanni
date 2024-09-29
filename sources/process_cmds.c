/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:48:38 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 23:07:48 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(t_mini minishell, int input_fd, int *out_fd, t_cmd *cmd)
{
	char	*path;
	char	**options;

	path = cmd->path;
	options = cmd->options;
	close(minishell.std_in);
	close(minishell.std_out);
	if (cmd->prev == NULL)
		close(out_fd[0]);
	setup_file_descriptors(input_fd, out_fd[1]);
	apply_heredoc(cmd);
	apply_redirections(cmd->redirs);
	if (is_built_in (cmd->str) != 0)
	{
		if (out_fd[1] != -1)
			close(out_fd[1]);
		if (input_fd != -1)
			close(input_fd);
		execute_built_in(&minishell, cmd);
		close(0);
		close(1);
		close(2);
		exit(0); //exit status da built in
	}
	else
	{
		free_token(&minishell.token);
		free(minishell.input);
		if (path != NULL)
			execve(path, options, __environ);
	}
	exit(EXIT_FAILURE);
}

pid_t	fork_and_execute(t_mini minishell, int input_fd, int *out_fd, t_cmd *cmd)
{
	pid_t	pid;

	if (is_built_in(cmd->str) != 0 && out_fd[1] == -1)
	{
		apply_redirections(cmd->redirs);
		execute_built_in(&minishell, cmd);
		dup2(minishell.std_in, 0);
		dup2(minishell.std_out, 1);
		close(minishell.std_in);
		close(minishell.std_out);
		return (0);
	}
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
	int			fd[2];
	const int	mock_fd[] = {0, -1};
	t_cmd		*current_cmd;
	int			*pids;
	int			i;

	current_cmd = minishell.cmd;
	pids = malloc(sizeof(int) * (count_cmd(minishell.token) + 1));
	i = 0;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
			create_pipe(fd);
		if (current_cmd->next == NULL)
			pids[i] = fork_and_execute(minishell, prev_fd, (int *) mock_fd,
					current_cmd);
		else
			pids[i] = fork_and_execute(minishell, prev_fd, fd, current_cmd);
		if (current_cmd->next != NULL)
			close_unused_fds(prev_fd, fd);
		else
			close_unused_fds(prev_fd, NULL);
		if (current_cmd->next != NULL)
			prev_fd = fd[0];
		else
			prev_fd = -1;
		current_cmd = current_cmd->next;
		i++;
	}
	pids[i] = -42;
	i = 0;
	while (pids[i] != -42)
	{
		waitpid(pids[i], &minishell.exit_status, 0);
		
	}
}
