/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:20 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/07 15:52:18 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setup_signals_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_quit_handle(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	execution_signals(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGQUIT, sig_quit_handle);
		signal(SIGINT, SIG_IGN);
	}
}

void	init_signals(void)
{
	signal(SIGINT, redonimation_readline);
	signal(SIGQUIT, SIG_IGN);
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
