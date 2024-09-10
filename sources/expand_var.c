/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/10 20:29:36 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//quero que esta função percorra a token list 
//ache as var para expandir em todos os casos 
//ignore casos que não serão expandidos
//cuidado com as aspas

// int	extra_len(t_mini *minishell, char *token)
// {
// 	char	*var;
// 	char	*exp;
// 	int		i;
// 	int		len_diff;

// 	i = 0;
// 	len_diff = 0;
// 	while (token[i] != '\0')
// 	{
// 		if (token[i] == '$' && is_valid(token[i + 1], 1))
// 		{
// 			var = return_var(&token[i]);
// 			if (var)
// 			{
// 				exp = return_key_content(minishell, var);
// 				if (exp != NULL)
// 					len_diff += ft_strlen(exp) - var_len(&token[i]);
// 				free(var);
// 			}
// 			i += var_len(&token[i]) + 1;
// 		}
// 		else
// 			i++;
// 	}
// 	return (len_diff);
// }

// void	copy_content(char *token, int *i, char *cont, int *j)
// {
// 	while (cont[*j] != '\0')
// 	{
// 		token[*i] = cont[*j];
// 		(*i)++;
// 		(*j)++;
// 	}
// }

char	*str_rest(const char *str, const char *var_name)
{
	size_t	var_len;
	size_t	rest_len;
	char	*rest;

	var_len = strlen(var_name);
	rest_len = strlen(str) - var_len;
	if (strncmp(str, var_name, var_len) == 0)
	{
		rest = (char *)malloc(rest_len + 1);
		if (!rest)
			return (NULL);
		strcpy(rest, str + var_len);
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
	exp = (ft_strjoin(key_content, rest));
	return (exp);
}

char	*expand_token(t_mini *minishell, char *token)
{
	char	**temp;
	char	*expanded;
	char	*key_content;
	int		i;

	expanded = ft_strdup("");
	i = 0;
	if (ft_strchr(token, '$') == NULL)
		return (ft_strdup(token));
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
