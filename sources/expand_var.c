/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/11 18:21:02 by asanni           ###   ########.fr       */
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
	//free (rest);
	return (exp);
}

char	*expand_token(t_mini *minishell, char *token)
{
	char	**temp;
	char	*expanded;
	char	*key_content;
	int		i;

	expanded = NULL;
	i = 0;
	if (ft_strchr(token, '$') == NULL)
		return (token);
	temp = ft_split(token, '$');
	if (!temp)
		return (NULL);
	while (temp[i] != NULL)
	{
		key_content = test(minishell, temp[i]);
		if (key_content != NULL)
			expanded = ft_strjoin(expanded, key_content);
		else
			expanded = ft_strjoin(expanded, temp[i]);
		i++;
	}
	free_matrix(temp);
	return (expanded);
}
