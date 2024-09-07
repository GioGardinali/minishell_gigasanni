/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:31:39 by asanni            #+#    #+#             */
/*   Updated: 2024/09/07 15:31:48 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_var(char *str)
{
	int	i;

	if (!str || str[0] != '$')
		return (0);
	if (!ft_isalpha(str[1]) && str[1] != '_')
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || (str[i] == '_')))
			return (0);
		i++;
	}
	return (1);
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

char	*env_check(t_mini *minishell, char *var_key)
{
	t_env	*current;

	current = minishell->env_exp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var_key) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

void	copy_content(char *token, int *i, char *cont)
{
	int	j;

	j = 0;
	while (cont[j] != '\0')
	{
		token[*i] = cont[j];
		(*i)++;
		j++;
	}
}
