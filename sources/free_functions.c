/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:45:06 by asanni            #+#    #+#             */
/*   Updated: 2024/07/27 19:29:20 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmds(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp != NULL)
	{
		temp = (*cmd)->next;
		free(cmd);
		(*cmd) = temp;
	}
	cmd = NULL;
}

void	free_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp != NULL)
	{
		temp = (*token)->next;
		free(token);
		(*token) = temp;
	}
	token = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

//void	free_cmds(t_cmd **cmd)
// {
// 	t_cmd	*temp;

// 	while (*cmd != NULL)
// 	{
// 		temp = (*cmd)->next;
// 		if ((*cmd)->str)
// 			free((*cmd)->str);
// 		if ((*cmd)->options)
// 			free_matrix((*cmd)->options);
// 		if ((*cmd)->path)
// 			free((*cmd)->path);
// 		free(*cmd);
// 		*cmd = temp;
// 	}
// 	*cmd = NULL;
// }
