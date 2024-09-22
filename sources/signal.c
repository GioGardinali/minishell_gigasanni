/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:20 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/21 03:09:25 by gigardin         ###   ########.fr       */
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
	if (signal == SIGINT)
	{
		printf("\nHeredoc interrupted by Ctrl+C\n");
		//clean_heredoc_files(minishell->cmd); // Limpa os arquivos temporários
		exit(EXIT_FAILURE);
	}
}
