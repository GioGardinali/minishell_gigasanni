/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/08/29 19:44:16 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pid(t_mini *minishell)
{
	if (minishell->cmd->path != NULL)
		process_multiple_cmds(*minishell, -1);
	free_token(&minishell->token);
	free(minishell->cmd->path);
	free_cmds(&minishell->cmd);
}

static void	start_minishell(t_mini *minishell)
{
	t_token	*token;

	token = NULL;
	minishell->input = readline("Minishelby> ");
	if (!minishell->input)
		minishell->input = ft_strdup("exit");
	if (minishell->input[0] == '\0' || (is_blank(minishell->input) == 1))
	{
		if (minishell->input[0] != '\0')
			add_history(minishell->input);
		return ;
	}
	else
		add_history(minishell->input);
	if (ft_strcmp(minishell->input, "exit") == 0)
		exit_function(minishell);
	norme(minishell, token);
	check_pid(minishell);
}

int	main(void)
{
	t_mini		minishell;

	minishell = (t_mini){0};
	copy_env(&minishell);
	while (42)
	{
		start_minishell(&minishell);
		if (minishell.cmd != NULL)
		{
			free(minishell.cmd->path);
			free_matrix(minishell.cmd->options);
			minishell.cmd->options = NULL;
			free_cmds(&minishell.cmd);
			minishell.cmd = NULL;
		}
		if (minishell.token != NULL)
			free_token_bc(&minishell.token);
		minishell.token = NULL;
	}
	free(minishell.env_content);
	return (0);
}
