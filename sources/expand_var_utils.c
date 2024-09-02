/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:31:39 by asanni            #+#    #+#             */
/*   Updated: 2024/09/02 19:44:23 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_valid_var(char c)
{
	return (isalpha(c) || isdigit(c) || (c == '_'));
}

int	var_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (ft_valid_var(str[i]))
			{
				len++;
				i++;
			}
			break ;
		}
		i++;
	}
	return (len);
}

char	*return_var(char *str)
{
	char	*var;
	int		len;
	int		i;
	int		j;

	len = var_len(str);
	i = -1;
	j = 0;
	var = malloc((len + 1) * sizeof(char));
	while (str[++i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (len > 0)
			{
				var[j] = str[i];
				len--;
				i++;
				j++;
			}
		}
	}
	var[j] = '\0';
	return (var);
}

int	env_check(t_mini *minishell)
{
	minishell->token
}

// char	*get_env_value(t_env *env_list, const char *key)
// {
// 	t_env	*current;

// 	current = env_list;
// 	while (current != NULL)
// 	{
// 		if (strcmp(current->key, key) == 0)
// 			return (current->content);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// void	expand_and_print_tokens(t_mini *minishell)
// {
// 	t_token	*current_token;
// 	char	*env_key;
// 	char	*value;

// 	current_token = minishell->token;
// 	env_key = NULL;
// 	value = NULL;
// 	while (current_token != NULL)
// 	{
// 		if (current_token->str[0] == '$')
// 		{
// 			env_key = current_token->str + 1;
// 			value = get_env_value(minishell->env_exp, env_key);
// 			if (value)
// 				printf("%s ", value);
// 			else
// 				printf("");
// 		}
// 		else
// 		{
// 			printf("%s ", current_token->str);
// 		}
// 		current_token = current_token->next;
// 	}
// 	printf("\n");
// }
