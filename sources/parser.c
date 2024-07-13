/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:21:55 by asanni            #+#    #+#             */
/*   Updated: 2024/07/13 15:47:16 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_built_ins(t_token *token)
{
	if (ft_strcmp(token->str, "echo") == 0)
		return ();
	if (ft_strcmp(token->str, "cd") == 0)
		return ();
	if (ft_strcmp(token->str, "pwd") == 0)
		return ();
	if (ft_strcmp(token->str, "export") == 0)
		return ();
	if (ft_strcmp(token->str, "env") == 0)
		return ();
	if (ft_strcmp(token->str, "exit") == 0)
		return ();
}

/*
BUILT INS
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/
