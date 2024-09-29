/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:29 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 21:00:42 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_exit(t_mini *minishell, t_cmd *cmd)
{
	t_cmd	*current;
	int		status;

	if (current->options[1])
	{
		//validar se esta dentro do range long max e min e se é numero
		//(caso não retorna 2 e printa erro)
		status = ft_atoi(current->options[1]);
	}
	else
		status = minishell->exit_status;
	ft_putendl_fd("exit", 1);
	free(minishell->env_content);
	free(minishell->input);
	clean_heredoc_files(minishell->cmd);
	free_cmds(&minishell->cmd);
	free_env(&minishell->env_exp);
	free_token(&minishell->token);
	close(minishell->std_in);
	close(minishell->std_out);
	exit(status);
}
