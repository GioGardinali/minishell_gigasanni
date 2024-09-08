/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:57:37 by asanni            #+#    #+#             */
/*   Updated: 2024/09/08 18:38:26 by asanni           ###   ########.fr       */
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
		if (token[i] == '$' && is_valid(token[i + 1], 1))
		{
			var = return_var(&token[i]);
			if (var)
			{
				exp = return_key_content(minishell, var);
				if (exp != NULL)
					len_diff += ft_strlen(exp) - var_len(&token[i]);
				free(var);
			}
			i += var_len(&token[i]) + 1;
		}
		else
			i++;
	}
	return (len_diff);
}

void	copy_content(char *token, int *i, char *cont, int *j)
{
	while (cont[*j] != '\0')
	{
		token[*i] = cont[*j];
		(*i)++;
		(*j)++;
	}
}

char	*expand_token(t_mini *minishell, char *token)
{
	char	*var;
	char	*exp;
	char	*new_token;
	int		new_len;
	int		i;

	var = return_var(token);
	exp = return_key_content(minishell, var);
	new_len = ft_strlen(token) + extra_len(minishell, token);
	new_token = malloc((sizeof(char) * (new_len + 1)));
	new_len = 0;
	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
			copy_content(new_token, &new_len, exp, &i);
		else
		{
			new_token[new_len] = token[i];
			new_len++;
			i++;
		}
	}
	new_token[new_len] = '\0';
	printf("%s\n", new_token);
	return (new_token);
}
