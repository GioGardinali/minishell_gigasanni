/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:29 by asanni            #+#    #+#             */
/*   Updated: 2024/09/22 17:32:00 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_function(t_mini *minishell)
{
	ft_putendl_fd("exit", 1);
	free(minishell->env_content);
	free(minishell->input);
	free_token(&minishell->token);
	exit(EXIT_SUCCESS);
}
