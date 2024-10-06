/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:29 by asanni            #+#    #+#             */
/*   Updated: 2024/10/06 16:34:19 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_options(char **options)
{
	long int	nbr;
	int			i;

	i = 0;
	while (options[i] != NULL)
		i++;
	if (i > 2)
	{
		print_error(options[2], ": too many options");
		return (1);
	}
	if (!ft_isdigit(options[1][0]) && options[1][0] != '-' &&
		options[1][0] != '+')
	{
		print_error(options[1], ": numeric argument required");
		return (2);
	}
	nbr = ft_atol(options[1]);
	if (nbr < LONG_MIN || nbr > LONG_MAX)
	{
		print_error(options[1], ": numeric argument required");
		return (2);
	}
	return (nbr % 256);
}

int	execute_exit(t_mini *minishell, t_cmd *cmd)
{
	t_cmd	*current;
	int		status;

	current = cmd;
	if (current->options[1])
		exit (exit_options(current->options));
	else
		status = minishell->exit_status;
	ft_putendl_fd("exit", 1);
	free(minishell->pids);
	free(minishell->env_content);
	free(minishell->input);
	clean_heredoc_files(minishell->cmd);
	free_cmds(&minishell->cmd);
	free_env(&minishell->env_exp);
	free_token(&minishell->token);
	close(minishell->std_in);
	close(minishell->std_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
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
