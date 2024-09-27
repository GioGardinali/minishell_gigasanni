/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:29 by asanni            #+#    #+#             */
/*   Updated: 2024/09/27 19:22:30 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_exit(t_mini *minishell)
{
	ft_putendl_fd("exit", 1);
	free(minishell->env_content);
	free(minishell->input);
	clean_heredoc_files(minishell->cmd);
	free_cmds(&minishell->cmd);
	free_env(&minishell->env_exp);
	free_token(&minishell->token);
	exit(EXIT_SUCCESS);
}
