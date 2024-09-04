/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/04 19:54:19 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//quero que esta função percorra a token list 
//ache as var para expandir em todos os casos 
//ignore casos que não serão expandidos
//cuidado com as aspas

int	extra_len(t_mini *minishell, char *token)
{
	char	*var;
	char	*exp;
	int		i;
	int		len_diff;

	i = 0;
	len_diff = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$' && ft_valid_var(token[i + 1]))
		{
			var = return_var(&token[i]);
			exp = env_check(minishell, var);
			if (exp != NULL)
				len_diff += strlen(exp) - (var_len(&token[i]) + 1);
			i += var_len(&token[i]) + 1;
			free(var);
		}
		else
			i++;
	}
	return (len_diff);
}

char	*expand_token(t_mini *minishell, char *token)
{
	char	*var;
	char	*exp;
	char	*new_token;
	int		new_len;
	int		i;

	var = return_var(token);
	exp = env_check(minishell, var);
	token = minishell->token->str;
	new_len = ft_strlen(token) + extra_len(minishell, token);
	new_token = malloc((sizeof(char) * (new_len + 1)));
	new_len = 0;
	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
			copy_content(new_token, &new_len, exp);
		else
		{
			new_token[new_len] = token[i];
			new_len++;
		}
		i++;
	}
	new_token[new_len] = '\0';
	return (new_token);
}
