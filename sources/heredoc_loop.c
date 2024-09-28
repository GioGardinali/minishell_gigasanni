/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:09:18 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/28 01:39:54 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_error_heredoc(int i, const char *eof)
{
	ft_printf("Minishelby: warning: here-document at line %d ", i);
	ft_printf("delimited by end-of-file (wanted `%s')\n", eof);
	return (2);
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
