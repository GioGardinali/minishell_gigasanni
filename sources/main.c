/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/08/21 20:24:39 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pid(t_mini *minishell)
{
	process_multiple_cmds(*minishell, -1);
	ft_putendl_fd("Execve falhou", 2);
	free_matrix(minishell->cmd->options);
	free(minishell->cmd->path);
	free(minishell->cmd);
	free_token_bc(&minishell->token);
	free_cmds(&minishell->cmd);
	free(minishell->env_content);
	exit(1);
}

static void	start_minishell(t_mini *minishell)
{
	pid_t	pid;
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
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		check_pid(minishell);
	free(minishell->input);
	waitpid(pid, NULL, 0);
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
			free_matrix(minishell.cmd->options);
			minishell.cmd->options = NULL;
			free(minishell.cmd);
			minishell.cmd = NULL;
		}
		if (minishell.token != NULL)
			free_token_bc(&minishell.token);
		minishell.token = NULL;
	}
	free(minishell.env_content);
	return (0);
}
