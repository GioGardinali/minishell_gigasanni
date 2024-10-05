/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/10/05 17:30:04 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pid(t_mini *minishell)
{
	if (is_built_in(minishell->cmd->str) || minishell->cmd->path != NULL)
		process_multiple_cmds(minishell, -1);
	else
	{
		print_error(minishell->cmd->str, ": command not found");
		update_exit_status(minishell, 127);
	}
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
	if (norme(minishell, token) == 0)
		check_pid(minishell);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_mini	minishell;

	minishell = (t_mini){0};
	(void) argc;
	(void) argv;
	copy_env(&minishell, env);
	make_env_list(&minishell);
	ft_global_mini(&minishell);
	while (42)
	{
		minishell.std_in = dup(STDIN_FILENO);
		minishell.std_out = dup(STDOUT_FILENO);
		init_signals();
		start_minishell(&minishell);
		clean_minishell(&minishell);
	}
	free_cmds(&minishell.cmd);
	free(minishell.env_content);
	return (0);
}
