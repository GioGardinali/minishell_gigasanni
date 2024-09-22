/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:09:18 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/22 16:09:48 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	loop_exec_heredoc(int fd, int quotes, const char *str_end)
{
	char	*line;
	char	*error;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error = "error"; //"("(wanted `%s')"\n, "Minishell:", "warning:", "here-document delimited by end-of-file". + str_end)";
			ft_putendl_fd(error, 2);
			break ;
		}
		if (ft_strcmp(line, str_end) == 0)
		{
			free(line);
			break ;
		}
		(void)quotes;
		// if (!quotes)
		// 	line = "aplicar aqui a expand_vars\n"; // expand_vars(line);
		ft_putendl_fd(line, fd);
		free(line);
	}
}
