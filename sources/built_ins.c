/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:21:55 by asanni            #+#    #+#             */
/*   Updated: 2024/09/21 02:57:30 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo"))
		return (ECHO);
	if (ft_strcmp(str, "cd"))
		return (CD);
	if (ft_strcmp(str, "pwd"))
		return (PWD);
	if (ft_strcmp(str, "export"))
		return (EXPT);
	if (ft_strcmp(str, "env"))
		return (ENV);
	if (ft_strcmp(str, "exit"))
		return (EXIT);
	return (0);
}

void	execute_built_in(t_mini *minishell, t_cmd *cmd)
{
	// if (is_built_in(cmd->str) == ECHO)
	// 	execute_echo(0);
	// if (is_built_in(cmd->str) == CD)
	// 	execute_cd();
	// if (is_built_in(cmd->str) == PWD)
	// 	execute_pwd();
	if (is_built_in(cmd->str) == EXPT)
		execute_export(minishell, cmd);
	// if (is_built_in(cmd->str) == ENV)
	// 	execute_env();
	// if (is_built_in(cmd->str) == EXIT)
	// 	execute_exit();
}

/* BUILT INS
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/
