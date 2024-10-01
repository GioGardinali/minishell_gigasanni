/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:23:18 by asanni            #+#    #+#             */
/*   Updated: 2024/10/01 19:04:05 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(t_mini *minishell, char **env_list)
{
	int		i;
	int		size;
	char	**temp;

	size = 0;
	i = -1;
	while (env_list[size])
		size++;
	temp = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		temp[i] = env_list[i];
	temp[i] = NULL;
	minishell->env_content = temp;
	return (minishell->env_content);
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

	path = ft_strchr(str, '/');
	return (path);
}

static char	*append_slash(char *path, char *cmd)
{
	char	*new_str;
	int		len;
	int		cmd_len;

	len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	new_str = malloc((len + cmd_len + 2) * sizeof(char));
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

	if (ft_strchr(str, '/') != NULL)
		return (ft_strdup(str));
	path_line = search_path(minishell->env_content, "PATH");
	str_path = ft_split(remove_path(path_line), ':');
	result = 1;
	i = 0;
	while (result != 0)
	{
		path = str_path[i];
		if (str_path[i] == NULL)
			break ;
		path = append_slash(str_path[i], str);
		result = access(path, F_OK | R_OK);
		if (result != 0)
			free(path);
		i++;
	}
	free_matrix(str_path);
	return (path);
}
