/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/21 02:23:00 by gigardin         ###   ########.fr       */
=======
/*   Updated: 2024/09/21 14:52:16 by asanni           ###   ########.fr       */
>>>>>>> 1d2d5319e22e26fa33fe1d4a23d32cb4a5d5977c
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_pid(t_mini *minishell)
{
	process_multiple_cmds(*minishell, -1);
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
	make_env_list(minishell);
	norme(minishell, token);
	check_pid(minishell);
}

int	main(void)
{
	t_mini		minishell;

	minishell = (t_mini){0};
	copy_env(&minishell);
	// make_env_list(&minishell);
	while (42)
	{
		start_minishell(&minishell);
		if (minishell.cmd != NULL)
		{
			clean_heredoc_files(minishell.cmd);
			free_cmds(&minishell.cmd);
		}
		if (minishell.token != NULL)
			free_token_bc(&minishell.token);
		minishell.token = NULL;
	}
	free_cmds(&minishell.cmd);
	free(minishell.env_content);
	return (0);
}
