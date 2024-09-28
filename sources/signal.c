/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:20 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/28 02:09:07 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	copy_heredoc(int signal)
// {
// 	t_mini	*shell;

// 	shell = ft_get_shell();
// 	if (signal == SIGINT)
// 	{
// 		shell->exit_status = 130;
// 		//clear_exit(shell, TRUE);
// 	}
// }

void	setup_signals_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	copy_heredoc(int signal)
{
	t_mini	*minishell;

	minishell = ft_global_mini(NULL);
	if (signal == SIGINT)
	{
		//printf("\nHeredoc interrupted by Ctrl+C\n");
		clean_heredoc_files(minishell->cmd);
		exit(EXIT_FAILURE);
	}
}

void	init_signals(void)
{
	signal(SIGINT, redonimation_readline);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	redonimation_readline(int signal)
{
	if (signal == SIGINT)
	{	
		ft_putendl_fd("", 1);
		rl_on_new_line();// Informa ao readline que a linha foi modificada	
		rl_replace_line("", 0); // Simula uma modificação na linha de comando
		rl_redisplay();// Redesenha a linha de comando
	}
}
