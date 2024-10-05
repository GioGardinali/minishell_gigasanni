/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:09:18 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/05 17:21:58 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error_heredoc(int i, const char *eof)
{
	write(2, "Minishelby: warning: here-document at line ", 43);
	ft_putnbr_fd(i, 2);
	write(2, " delimited by end-of-file (wanted `", 35);
	while (*eof)
	{
		write(2, eof, 1);
		eof++;
	}
	write(2, "')\n", 4);
}

void	loop_exec_heredoc(int fd, int quotes, const char *str_end,
			t_mini *minishell)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error_heredoc(i, str_end);
			break ;
		}
		if (ft_strcmp(line, str_end) == 0)
		{
			free(line);
			break ;
		}
		process_line(line, fd, quotes, minishell);
		i++;
	}
}

void	process_line(char *line, int fd, int quotes, t_mini *minishell)
{
	t_aux	aux;

	if (!quotes)
	{
		aux.token = line;
		line = expand_token(minishell, &aux, !quotes);
	}
	ft_putendl_fd(line, fd);
	free(line);
}

int	execute_heredoc(const char *delimiter, unsigned int count_cmd,
	t_heredoc *heredocs, t_token *token)
{
	char	*filename;
	int		exit_status;
	int		validate;
	int		is_first_cmd;

	is_first_cmd = (token->prev == NULL);
	validate = 0;
	delimiter = ft_strdup(delimiter);
	setup_signals_heredoc();
	filename = get_file(is_first_cmd);
	free(token->next->str);
	token->next->str = filename;
	if (!handle_filename(filename, heredocs, count_cmd))
		return (0);
	exit_status = 0;
	exit_status = handle_fork(filename, delimiter, heredocs);
	free((char *)delimiter);
	if (exit_status == 130)
		return (validate);
	else
		validate = 1;
	return (validate);
}
