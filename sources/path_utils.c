/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:23:18 by asanni            #+#    #+#             */
/*   Updated: 2024/06/28 18:48:23 by asanni           ###   ########.fr       */
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

char	*search_path(char **s, char *str)
{
	char	*str_path;

	while (*s != NULL)
	{
		if (ft_strncmp(*s, str, 4) == 0)
			return (*s);
		s++;
	}
	return (NULL);
}

char	**copy_env(void)
{
	int		i;
	int		size;
	char	**temp;

	size = 0;
	i = -1;
	while (__environ[size])
		size++;
	temp = ft_calloc(sizeof(char *), size + 1);
	while (++i < size)
		temp[i] = __environ[i];
	// i = -1;
	// while (++i < size)
	// 	printf("%s\n", temp[i]);
	return (temp);
}

char	*remove_path(char *str)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_strchr(str, '/');
	return (path);
}
