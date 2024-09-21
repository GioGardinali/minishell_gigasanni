/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:18:36 by asanni            #+#    #+#             */
/*   Updated: 2024/09/21 14:00:00 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_export(t_mini *minishell, t_cmd *cmd)
{
	if (!cmd->options[1])
		print_export(minishell);
	else
		export_options(minishell, cmd);
}
