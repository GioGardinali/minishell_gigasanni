/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:39 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/07 15:54:51 by asanni           ###   ########.fr       */
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
	heredoc->array = ft_calloc(sizeof(t_file_heredoc *), heredoc->size + 1);
	if (!heredoc->array)
	{
		free(heredoc);
		return (NULL);
	}
	return (heredoc);
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

t_mini	*ft_global_mini(t_mini *minishell)
{
	static t_mini	*shell;

	if (shell == NULL)
		shell = minishell;
	return (shell);
}

void	quit_heredocs(t_heredoc *heredocs)
{
	int				i;
	t_file_heredoc	*current_file;
	t_file_heredoc	*next_file;

	i = 0;
	if (!heredocs)
		return ;
	if (!heredocs->array)
	{
		free(heredocs);
		return ;
	}
	while (heredocs->array[i++])
	{
		current_file = heredocs->array[i];
		while (current_file)
		{
			next_file = current_file->next;
			free(current_file->file);
			free(current_file);
			current_file = next_file;
		}
	}
	free(heredocs->array);
	free(heredocs);
}

int	handle_fork(char *filename, const char *delimiter, t_heredoc *heredocs)
{
	pid_t	pid;
	int		exit_status;
	t_mini	*minishell;
	t_token	*next;

	minishell = ft_global_mini(NULL);
	exit_status = 0;
	pid = fork();
	if (pid == 0)
	{
		close_std_int_and_out(minishell);
		write_file(filename, check_quotes_in_token(delimiter),
			remove_quotes(delimiter), minishell);
		free((char *)delimiter);
		quit_heredocs(heredocs);
		free(minishell->input);
		free(minishell->env_content);
		next = minishell->token->next;
		clean_fork_heredoc(minishell);
		exit(0);
	}
	waitpid(pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}
