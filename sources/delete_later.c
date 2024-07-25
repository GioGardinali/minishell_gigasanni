/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:12:09 by asanni            #+#    #+#             */
/*   Updated: 2024/07/25 15:13:13 by asanni           ###   ########.fr       */
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
