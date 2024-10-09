/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:38:49 by asanni            #+#    #+#             */
/*   Updated: 2024/10/09 19:04:15 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_env(t_mini *minishell, char *pwd, char *path)
{
	char	old_pwd[5000];
	char	new_pwd[5000];

	ft_memmove(old_pwd, "OLDPWD=", 8);
	ft_memmove(&old_pwd[ft_strlen(old_pwd)], pwd, ft_strlen(pwd) + 1);
	if (return_key_content(minishell, "OLDPWD") == NULL)
		list_env(&minishell->env_exp, old_pwd);
	else
		put_new_value(minishell, old_pwd);
	ft_memmove(new_pwd, "PWD=", 5);
	ft_memmove(&new_pwd[ft_strlen(new_pwd)], path, ft_strlen(path) + 1);
	if (return_key_content(minishell, "PWD") == NULL)
		list_env(&minishell->env_exp, new_pwd);
	else
		put_new_value(minishell, new_pwd);
	free(path);
}

void	get_pwd(t_mini *minishell, char pwd[])
{
	char	*var;

	var = return_key_content(minishell, "PWD");
	if (var == NULL)
	{
		var = getcwd(NULL, 0);
		if (var == NULL)
			ft_memset(pwd, '\0', 1);
		else
			ft_memmove(pwd, var, ft_strlen(var) + 1);
		free(var);
	}
	else
	{
		ft_memmove(pwd, var, ft_strlen(var) + 1);
	}
}

int	execute_cd(t_mini *minishell)
{
	char	*path;
	char	pwd[3000];

	path = minishell->cmd->options[1];
	if (minishell->cmd->options[2] != NULL)
		return (1);
	else if (minishell->cmd->options[1] == NULL)
	{
		path = return_key_content(minishell, "HOME");
		if (!path)
		{
			print_error("", "HOME is not set!");
			return (1);
		}
	}
	get_pwd(minishell, pwd);
	if (chdir(path) == -1)
	{
		perror(path);
		return (1);
	}
	update_env(minishell, pwd, getcwd(NULL, 0));
	return (0);
}
