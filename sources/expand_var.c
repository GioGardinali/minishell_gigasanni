/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/11 20:15:18 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//quero que esta função percorra a token list 
//ache as var para expandir em todos os casos 
//ignore casos que não serão expandidos
//cuidado com as aspas

char	*str_rest(const char *str, const char *var_name)
{
	size_t	var_len;
	size_t	rest_len;
	char	*rest;

	var_len = ft_strlen(var_name);
	rest_len = ft_strlen(str) - var_len;
	if (ft_strncmp(str, var_name, var_len) == 0)
	{
		rest = ft_strdup(str + var_len);
		return (rest);
	}
	return (NULL);
}

char	*test(t_mini *minishell, char *str)
{
	char	*var;
	char	*key_content;
	char	*rest;
	char	*exp;

	var = return_var(str);
	key_content = return_key_content(minishell, var);
	rest = str_rest(str, var);
	exp = ft_strjoin(key_content, rest);
	return (exp);
}

// char	*expand_token(t_mini *minishell, char *token)
// {
// 	char	**temp;
// 	char	*expanded;
// 	char	*key_content;
// 	int		i;

// 	expanded = ft_strdup("");
// 	i = 0;
// 	if (ft_strchr(token, '$') == NULL)
// 		return (token);
// 	temp = ft_split(token, '$');
// 	if (!temp)
// 		return (NULL);
// 	while (temp[i] != NULL)
// 	{
// 		key_content = test(minishell, temp[i]);
// 		if (key_content != NULL)
// 			expanded = ft_strjoin(expanded, key_content);
// 		else
// 			expanded = ft_strjoin(expanded, temp[i]);
// 		i++;
// 	}
// 	free_matrix(temp);
// 	return (expanded);
// }

char	*expand_token(t_mini *minishell, char *token)
{
	char	**temp;
	char	*expanded;
	char	*key_content;
	char	*new_expanded;
	int		i;
	char	*dollar_pos;

	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	dollar_pos = ft_strchr(token, '$');
	if (dollar_pos == NULL)
		return (ft_strdup(token));
	if (token != dollar_pos)
	{
		char *prefix = ft_substr(token, 0, dollar_pos - token);
		new_expanded = ft_strjoin(expanded, prefix);
		free(expanded);
		expanded = new_expanded;
		free(prefix);
	}
	temp = ft_split(dollar_pos, '$');
	if (!temp)
	{
		free(expanded);
		return (NULL);
	}
	i = 0;
	while (temp[i] != NULL)
	{
		key_content = test(minishell, temp[i]);
		if (key_content != NULL)
			new_expanded = ft_strjoin(expanded, key_content);
		else
			new_expanded = ft_strjoin(expanded, temp[i]);
		free(expanded);
		expanded = new_expanded;
		if (key_content)
			free(key_content);
		i++;
	}
	free_matrix(temp);
	return (expanded);
}
