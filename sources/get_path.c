/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:23:18 by asanni            #+#    #+#             */
/*   Updated: 2024/07/22 19:54:34 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Pegar o PATH certo
// Passar a split pelo path
// Concatenar com o comando (ex: /pasta/comando - /usr/bin/ls)
// Checar se a pasta especifica tem acesso ao comando

char	**copy_env(t_mini *minishell)
{
	int		i;
	int		size;
	char	**temp;

	size = 0;
	i = -1;
	while (__environ[size])
		size++;
	temp = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		temp[i] = __environ[i];
	temp[i] = NULL;
	minishell->env.env_content = temp;
	return (minishell->env.env_content);
}

static char	*search_path(char **s, char *str)
{
	while (*s != NULL)
	{
		if (ft_strncmp(*s, str, 4) == 0)
			return (*s);
		s++;
	}
	return (NULL);
}

static char	*remove_path(char *str)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_strchr(str, '/');
	return (path);
}

static char	*append_slash(char *path, char *cmd)
{
	static char	new_str[4096];
	int			len;
	int			cmd_len;

	len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	ft_strlcpy(new_str, path, len + 1);
	ft_strlcpy(&new_str[len], "/", 2);
	ft_strlcpy(&new_str[len + 1], cmd, cmd_len + 1);
	return (new_str);
}

char	*verify_path(t_mini *minishell, char *str)
{
	char	**str_path;
	char	*path_line;
	char	*path;
	int		result;
	int		i;

	path_line = search_path(minishell->env.env_content, "PATH");
	str_path = ft_split(remove_path(path_line), ':');
	result = 1;
	i = 0;
	while (result != 0)
	{
		path = str_path[i];
		if (str_path[i] == NULL)
			break ;
		path = append_slash(str_path[i], str);
		result = access(append_slash(str_path[i], str), F_OK | R_OK);
		i++;
	}
	if (result == -1)
		perror("Erro ao acessar o arquivo:");
	return (path);
}
