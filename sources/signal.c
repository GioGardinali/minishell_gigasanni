/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:20 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/27 19:42:40 by gigardin         ###   ########.fr       */
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
