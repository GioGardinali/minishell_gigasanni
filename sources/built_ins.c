/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:21:55 by asanni            #+#    #+#             */
/*   Updated: 2024/09/25 17:15:04 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(str, "cd") == 0)
		return (CD);
	if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(str, "export") == 0)
		return (EXPT);
	if (ft_strcmp(str, "unset") == 0)
		return (UNST);
	if (ft_strcmp(str, "env") == 0)
		return (ENV);
	if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	return (0);
}

void	execute_built_in(t_mini *minishell, t_cmd *cmd)
{
	if (is_built_in(cmd->str) == ECHO)
		execute_echo(cmd);
	if (is_built_in(cmd->str) == CD)
		execute_cd(cmd);
	// if (is_built_in(cmd->str) == PWD)
	// 	execute_pwd();
	if (is_built_in(cmd->str) == EXPT)
		execute_export(minishell, cmd);
	if (is_built_in(cmd->str) == UNST)
		execute_unset(minishell, cmd);
	if (is_built_in(cmd->str) == ENV)
		execute_env(minishell);
	if (is_built_in(cmd->str) == EXIT)
		exit_function(minishell);
}

/* BUILT INS
◦ cd with only a relative or absolute path
◦ pwd with no options
*/
