/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:23:18 by asanni            #+#    #+#             */
/*   Updated: 2024/06/26 17:13:57 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Pegar o PATH certo
// Passar a split pelo path
// Concatenar com o comando (ex: /pasta/comando - /usr/bin/ls)
// Checar se a pasta especifica tem acesso ao comando

// char	*check_path(t_mini *minishell)
// {
// 	// char *path_temp;
// 	// if (minishell->env_args)
// }

const char *search_path(const char **s, const char *str)
{
	while (*s!= NULL)
	{
		if (ft_strcmp(*s, str) == 0)
			return *s;
		s++;
	}
	return NULL;
}
