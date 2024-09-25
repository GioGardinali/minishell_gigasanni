/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:39 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/24 20:05:24 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_heredoc	*init_heredoc(t_mini *minishell)
{
	t_heredoc	*heredoc;

	heredoc = ft_calloc(sizeof(t_heredoc), 1);
	if (!heredoc)
		return (NULL);
	heredoc->size = count_cmd(minishell->token);
	heredoc->array = ft_calloc(sizeof(t_file_heredoc *), heredoc->size);
	if (!heredoc->array)
	{
		free(heredoc);
		return (NULL);
	}
	return (heredoc);
}

void	setup_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	handle_filename(char *filename, t_heredoc *heredocs,
	unsigned int count_cmd)
{
	if (!filename)
	{
		perror("get_file");
		return (0);
	}
	add_file(&heredocs->array[count_cmd], new_file(filename));
	return (1);
}

int	handle_fork(char *filename, const char *delimiter)
{
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == 0)
		write_file(filename, check_quotes_in_token(delimiter),
			remove_quotes(delimiter));
	waitpid(pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

int	execute_heredoc(const char *delimiter, unsigned int count_cmd,
	t_heredoc *heredocs, int is_first_cmd)
{
	char	*filename;
	int		exit_status;
	int		validate;

	validate = 0;
	setup_signals();
	filename = get_file(is_first_cmd);
	if (!handle_filename(filename, heredocs, count_cmd))
		return (0);
	exit_status = 0;
	exit_status = handle_fork(filename, delimiter);
	if (exit_status == 130)
		return (validate);
	else
		validate = 1;
	return (validate);
}
