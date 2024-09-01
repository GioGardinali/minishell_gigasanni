/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:12:09 by asanni            #+#    #+#             */
/*   Updated: 2024/09/01 14:44:07 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_matrix(char **matrix)
{
	if (matrix == NULL)
		return ;
	for (int i = 0; matrix[i]; i++)
	{
		printf("%s\n", matrix[i]);
	}
}

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		printf("Token: |%s| -> Type: %d,\n", current->str, current->type);
		current = current->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
	t_cmd	*current = cmd;

	while (current != NULL)
	{
		printf("Command: %s\n", current->str ? current->str : "NULL");
		print_options(current->options);
		printf("Path: %s\n", current->path ? current->path : "NULL");
		current = current->next;
		printf("\n");
	}
}

// Função auxiliar para imprimir as opções
void	print_options(char **options)
{
	if (options == NULL)
	{
		printf("Options: NULL\n");
		return ;
	}
	printf("Options:\n");
	while (*options != NULL)
	{
		printf("  %s\n", *options);
		options++;
	}
}

void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->content);
		current = current->next;
	}
}
