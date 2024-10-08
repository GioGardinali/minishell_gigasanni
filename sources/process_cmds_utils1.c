/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:05:01 by asanni            #+#    #+#             */
/*   Updated: 2024/10/08 19:37:43 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_nodes(t_mini *minishell)
{
	t_env	*current;
	int		node;

	node = 0;
	current = minishell->env_exp;
	current = current->next;
	while (current != NULL)
	{
		current = current->next;
		node++;
	}
	return (node);
}

static char	*create_env(t_env *env)
{
	char	*new_str;
	int		len;
	int		cmd_len;

	len = ft_strlen(env->key);
	cmd_len = ft_strlen(env->content);
	new_str = malloc((len + cmd_len + 2) * sizeof(char));
	ft_strlcpy(new_str, env->key, len + 1);
	ft_strlcpy(&new_str[len], "=", 2);
	ft_strlcpy(&new_str[len + 1], env->content, cmd_len + 1);
	return (new_str);
}

void	fill_env_content(t_mini *minishell)
{
	t_env	*current;
	int		i;

	i = 0;
	current = minishell->env_exp->next;
	minishell->env_content = malloc(sizeof (char *) *(count_nodes
				(minishell) + 1));
	while (current != NULL)
	{
		minishell->env_content[i] = create_env(current);
		current = current->next;
		i++;
	}
	minishell->env_content[i] = NULL;
}
