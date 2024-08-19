/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:20 by gigardin          #+#    #+#             */
/*   Updated: 2024/08/19 19:20:34 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_heredoc(int signal)
{
	t_mini	*shell;

	shell = ft_get_shell();
	if (signal == SIGINT)
	{
		shell->exit_status = 130;
		//clear_exit(shell, TRUE);
	}
}
