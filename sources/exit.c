/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:29 by asanni            #+#    #+#             */
/*   Updated: 2024/10/01 19:51:17 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_options(char *options)
{
	long int	nbr;

	nbr = ft_atol(options);
	if (ft_isdigit(options[0]) != 0)
	{
		print_error(options, ":requires a numeric argument");
		return (2);
	}
	if (nbr < LONG_MAX || nbr > LONG_MIN)
		return (nbr % 255);
	else
	{
		print_error(options, ":requires a numeric argument");
		return (2);
	}
}

int	execute_exit(t_mini *minishell, t_cmd *cmd)
{
	t_cmd	*current;
	int		status;

	current = cmd;
	if (current->options[1])
		return (exit_options(current->options[1]));
	else
		status = minishell->exit_status;
	ft_putendl_fd("exit", 1);
	free(minishell->env_content);
	free(minishell->input);
	clean_heredoc_files(minishell->cmd);
	free_cmds(&minishell->cmd);
	free_env(&minishell->env_exp);
	free_token(&minishell->token);
	close(minishell->std_in);
	close(minishell->std_out);
	exit(status);
}

int	update_exit_status(t_mini *minishell, int status)
{
	t_env	*current;

	current = minishell->env_exp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "?") == 0)
		{
			free (current->content);
			current->content = ft_itoa(status);
			break ;
		}
		current = current->next;
	}
	return (0);
}
