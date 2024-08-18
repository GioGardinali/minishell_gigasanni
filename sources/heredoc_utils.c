/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:30:41 by gigardin          #+#    #+#             */
/*   Updated: 2024/08/18 16:28:01 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes_in_token(char *str)
{
	int		validate;
	int		i;

	validate = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			validate = 1;
			return (validate);
		}
		i++;
	}
	return (validate);
}
char	*remove_quotes(char *str_end)
{
	int		len;
	char	*new;
	char	*temp;
	int		i;

	if (!check_quotes_in_token(str_end))
		return (ft_strdup(str_end));
	len = ft_strlen(str_end);
	new = ft_calloc(sizeof(char *), len + 1);
	temp = new;
	while (str_end[i])
	{
		if (str_end[i] != 34 && str_end[i] != 39)
		{
			*temp = str_end[i];
			temp++;
		}
		i++;
	}
	return (new);
}

int unsigned count_cmd(t_token *temp_token)
{
	int unsigned	count;

	count = 0;
	while (temp_token)
	{
		if (temp_token->type == PIPE)
			count++;
		temp_token = temp_token->next;
	}
	return (count + 1); // add + 1 para contar ultimo comando que não é seguido por PIPE
}

void	free_here_docs(t_heredoc **heredoc)
{
	int unsigned	i;
	t_file_heredoc	*next;
	t_file_heredoc	*current;

	if (!*heredoc)
		return ;
	i = 0;
	while (i < (*heredoc)->size)
	{
		current = (*heredoc)->array[i];
		while (current)
		{
			next = current->next;
			free(current->file);
			free(current);
			current = next;
		}
		i++;
	}
	free((*heredoc)->array);
	free(*heredoc);
	*heredoc = NULL;
}