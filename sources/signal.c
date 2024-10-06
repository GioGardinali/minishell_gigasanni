/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:20 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/05 18:15:47 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
