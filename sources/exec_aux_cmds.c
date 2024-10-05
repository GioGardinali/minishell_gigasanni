/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:51:49 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/05 15:52:40 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execve_function(t_mini *minihell, char *path, char **options)
{
	free_token(&minihell->token);
	free(minihell->input);
	if (path != NULL)
		execve(path, options, minihell->env_content);
}

void	close_std_int_and_out(t_mini *minishell)
{
	close(minishell->std_in);
	close(minishell->std_out);
}
