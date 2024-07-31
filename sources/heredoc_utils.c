/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:30:41 by gigardin          #+#    #+#             */
/*   Updated: 2024/07/31 19:57:03 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file_heredoc	*new_file(char *file)
{
	t_file_heredoc	*n_file;

	n_file = ft_calloc(1, sizeof(t_file_heredoc));
	n_file->file = file;
	return (n_file);
}

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