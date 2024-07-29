/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:39 by gigardin          #+#    #+#             */
/*   Updated: 2024/07/29 20:01:13 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_here_docs(t_mini *minishell)
{
	t_token	*temp_token;
	t_mini	*temp_minishell;
	int		validate;
	int		cmd_index; //para contabilizar todos cmds que tenho até chegar no hd
	
	validate = 0;
	cmd_index = 0;
	temp_minishell = minishell;
	temp_token = minishell->token;
	init_heredoc(temp_minishell);
	
	while(temp_token)
	{
		if (temp_token->type == PIPE)
			cmd_index++;
		else if (temp_token->type == HERE_DOC)
		{
			;// if (!execute_heredoc(temp_token->next->str, cmd_index, minishell->heredocs, temp_token->prev = NULL))//função para executar o heredoc, chamar aqui e checando erro se não for o primeiro
			// 	return (validate);
		}
		temp_token = temp_token->next;
		
	}

	return (validate);
}
static void	init_heredoc(t_mini *temp_minishell)
{
	t_heredoc	*heredoc;
	
	heredoc = ft_calloc(sizeof(t_heredoc), 1);
	heredoc->size = count_cmd(temp_minishell->token);
	heredoc->array = ft_calloc(sizeof(t_file_heredoc *), heredoc->size);
	temp_minishell->heredocs = heredoc;
}

// static int	execute_heredoc(char *str, int unsigned index, t_heredoc *heredoc, int is_first)
// {
// 	int	validate;
// 	validate = 0;

// 	return (validate);
// }