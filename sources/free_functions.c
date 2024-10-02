/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:45:06 by asanni            #+#    #+#             */
/*   Updated: 2024/10/02 20:04:38 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmds(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp != NULL)
	{
		temp = (*cmd)->next;
		if ((*cmd)->path)
			free((*cmd)->path);
		free_redirs((*cmd)->redirs);
		free_matrix((*cmd)->options);
		free((*cmd)->str);
		free(*cmd);
		(*cmd) = temp;
	}
	cmd = NULL;
}

void	free_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		temp = (*env)->next;
		free((*env)->key);
		free((*env)->content);
		free(*env);
		(*env) = temp;
	}
	env = NULL;
}

void	free_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp != NULL)
	{
		temp = (*token)->next;
		free((*token)->str);
		free(*token);
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
	if (matrix)
		free(matrix);
}
