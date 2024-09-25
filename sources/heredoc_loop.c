/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:09:18 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/25 19:16:49 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	loop_exec_heredoc(int fd, int quotes, const char *str_end, t_mini *minishell)
{
	char	*line;
	char	*error;
	t_aux	aux;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error = "error: here-document delimited by end-of-file (wanted `%s')\n";
			ft_putendl_fd(error, 2); // Mensagem de erro
			break ;
		}
		if (ft_strcmp(line, str_end) == 0) // Se o final do here-doc foi encontrado
		{
			free(line);
			break ;
		}
		if (!quotes) // Apenas expande variáveis se não estiver entre aspas
		{
			aux.token = line;
			line = expand_token(minishell, &aux, !quotes); // Expande a linha
		}
		ft_putendl_fd(line, fd); // Escreve no arquivo
		free(line);
	}
}
// void	loop_exec_heredoc(int fd, int quotes, const char *str_end)
// {
// 	char	*line;
// 	char	*error;
// 	// char	**split;
// 	// int		i;
// 	// t_mini	*tmp_minishell;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			error = "error"; //"("(wanted `%s')"\n, "Minishell:", "warning:", "here-document delimited by end-of-file". + str_end)";
// 			ft_putendl_fd(error, 2);
// 			break ;
// 		}
// 		if (ft_strcmp(line, str_end) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		(void)quotes;
// 		// if (!quotes)
// 		// {			
// 		// 	line = adjust_spaces(tmp_minishell->input);
// 		// 	split = ft_split(line, -1);
// 		// 	while (split[i] != NULL)
// 		// 		make_tokens(&tmp_minishell->token, split[i++]);// expand_vars(line);
// 		// 	expand_all_tokens(tmp_minishell);
// 		// }
// 		ft_putendl_fd(line, fd);
// 		free(line);
// 	}
// }
