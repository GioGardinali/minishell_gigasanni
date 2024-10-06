/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:48:38 by asanni            #+#    #+#             */
/*   Updated: 2024/10/06 19:40:08 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(t_mini minishell, int input_fd, int *out_fd, t_cmd *cmd)
{
	char	*path;
	char	**options;
	int		status;

	path = cmd->path;
	options = cmd->options;
	close_std_int_and_out(&minishell);
	if (cmd->prev != NULL || cmd->next != NULL)
		close(out_fd[0]);
	setup_file_descriptors(input_fd, out_fd[1]);
	if (apply_redirections(cmd->redirs) == FAIL)
	{
		if (is_built_in(cmd->str))
		{
			if (out_fd[1] != -1)
				close(out_fd[1]);
			if (input_fd != -1)
				close(input_fd);
		}
		clean_exec_comand(&minishell);
		minishell.exit_status = 1;
	}
	else if (is_built_in (cmd->str) != 0)
	{
		if (out_fd[1] != -1)
			close(out_fd[1]);
		if (input_fd != -1)
			close(input_fd);
		execute_built_in(&minishell, cmd);
		status = minishell.exit_status;
		clean_exec_comand(&minishell);
		exit(status);
	}
	else
		execve_function(&minishell, path, options);
	exit(minishell.exit_status);
}

/*verificar se o path é válido no process cmds*/

pid_t	fork_and_execute(t_mini *minishell, int input_fd,
	int *out_fd, t_cmd *cmd)
{
	pid_t	pid;

	if (is_built_in(cmd->str) != 0 && out_fd[1] == -1)// && cmd->prev == NULL)
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

void	process_multiple_cmds(t_mini *minishell, int prev_fd)
{
	int			fd[2];
	const int	mock_fd[] = {0, -1};
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
	current_cmd = minishell->cmd;
	if (current_cmd->next == NULL && is_built_in(current_cmd->str) != 0)
	{
		update_exit_status(minishell, minishell->exit_status);
		free(minishell->pids);
		return ;
	}
	pids[i] = -42;
	i = 0;
	while (pids[i] != -42)
	{
		waitpid(pids[i], &minishell->exit_status, 0);
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		update_exit_status(minishell, minishell->exit_status);
		i++;
	}
	free(pids);
}
