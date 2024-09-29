/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:18:36 by asanni            #+#    #+#             */
/*   Updated: 2024/09/28 21:13:36 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_export(t_mini *minishell, t_cmd *cmd)
{
	if (!cmd->options[1])
		return (print_export(minishell));
	else
		return (export_options(minishell, cmd));
}
