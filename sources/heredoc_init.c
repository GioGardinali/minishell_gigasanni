/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:39 by gigardin          #+#    #+#             */
/*   Updated: 2024/07/31 19:52:04 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_heredoc(t_mini *temp_minishell)
{
	t_heredoc	*heredoc;
	
	heredoc = ft_calloc(sizeof(t_heredoc), 1);
	heredoc->size = count_cmd(temp_minishell->token);
	heredoc->array = ft_calloc(sizeof(t_file_heredoc *), heredoc->size);
	temp_minishell->heredocs = heredoc;
}

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
			temp_minishell->heredocs->array[0] = new_file(temp_token->str);
			printf("%s", temp_minishell->heredocs->array[0]->file);
			// if (!execute_heredoc(temp_token->next->str, cmd_index, minishell->heredocs, temp_token->prev = NULL))//função para executar o heredoc, chamar aqui e checando erro se não for o primeiro
			// 	return (validate);
		}
		temp_token = temp_token->next;
		
	}

	return (validate);
}

// static int	execute_heredoc(char *str, int unsigned index, t_heredoc *heredoc, int is_first)
// {
// 	int	validate;
// 	validate = 0;

// 	return (validate);
// }