/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 02:29:52 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/07 19:57:59 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setup_file_descriptors(int input_fd, int out_fd)
{
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
}

void	close_fds(int *out_fd, int input_fd)
{
	if (out_fd[1] != -1)
		close(out_fd[1]);
	if (input_fd != -1)
		close(input_fd);
}

void	wait_and_update_exit_status(t_mini *minishell, int *pids)
{
	int	i;

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

int	is_first_and_builtin(t_mini *minishell)
{
	if (minishell->cmd->next == NULL && is_built_in(minishell->cmd->str) != 0)
	{
		update_exit_status(minishell, minishell->exit_status);
		free(minishell->pids);
		return (1);
	}
	return (0);
}

int	return_pid(t_mini *minishell, t_cmd *cmd, int prev_fd, int fd[])
{
	const int	mock_fd[] = {0, -1};

	if (cmd->next == NULL)
		return (fork_and_execute(minishell, prev_fd, (int *) mock_fd, cmd));
	else
		return (fork_and_execute(minishell, prev_fd, fd, cmd));
}
