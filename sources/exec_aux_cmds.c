/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:51:49 by gigardin          #+#    #+#             */
/*   Updated: 2024/10/05 20:17:36 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_file_path_access(char *path, int permission, char **options)
{
	struct stat	path_stat;

	if (!path)
	{
		print_error(options[0], ": Command not found");
		return (127);
	}
	stat(path, &path_stat);
	if (access(path, F_OK) != 0)
	{
		print_error(options[0], ": No such file or directory");
		return (127);
	}
	if (access(path, permission))
	{
		print_error(options[0], ": Permission denied");
		return (126);
	}
	if (S_ISDIR(path_stat.st_mode) && ft_strcmp(options[0], path) == 0)
	{
		print_error(options[0], ": Is a directory");
		return (126);
	}
	return (0);
}

void	execve_function(t_mini *minishell, char *path, char **options)
{
	int	status;

	status = 0;
	free_token(&minishell->token);
	free(minishell->input);
	status = check_file_path_access(path, X_OK, options);
	if (status == 0)
	{
		execve(path, options, minishell->env_content);
		minishell->exit_status = 1;
	}
	else
		minishell->exit_status = status;
	close(0);
	close(1);
}

void	close_std_int_and_out(t_mini *minishell)
{
	close(minishell->std_in);
	close(minishell->std_out);
}
