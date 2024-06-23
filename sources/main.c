/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/06/23 16:41:22 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void start_minishell(t_mini *minishell)
{
	minishell->input = readline("Minishelby> ");
}

int main (void)
{
	t_mini minishell;
	minishell = (t_mini){0};
	//minishell.env_args = getenv(__environ);
	while (1)
		start_minishell(&minishell);
	//free_envs(minishell.env_args);
	return (0);

}
