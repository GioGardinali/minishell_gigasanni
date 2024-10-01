/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/10/01 20:19:32 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pid(t_mini *minishell)
{
	if ((!is_built_in(minishell->cmd->str)) && minishell->cmd->path == NULL)
	{
		print_error(minishell->cmd->str, ": command not found");
		update_exit_status(minishell, 127);
		return ;
	}
	else
		process_multiple_cmds(minishell, -1);
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

int	main(int argc, char **argv, char **env )
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
		if (minishell.cmd != NULL)
		{
			clean_heredoc_files(minishell.cmd);
			free_cmds(&minishell.cmd);
		}
		if (minishell.token != NULL)
			free_token(&minishell.token);
		free_cmds(&minishell.cmd);
		minishell.token = NULL;
		close(minishell.std_in);
		close(minishell.std_out);
	}
	free_cmds(&minishell.cmd);
	free(minishell.env_content);
	return (0);
}
