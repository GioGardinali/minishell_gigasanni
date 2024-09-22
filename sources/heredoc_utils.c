/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:30:41 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/22 16:49:36 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes_in_token(const char *str)
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

char	*remove_quotes(const char *str_end)
{
	int		len;
	char	*new;
	char	*temp;
	int		i;

	i = 0;
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

unsigned int	count_cmd(t_token *temp_token)
{
	unsigned int	count;

	count = 0;
	while (temp_token)
	{
		if (temp_token->type == PIPE)
			count++;
		temp_token = temp_token->next;
	}
	return (count + 1); // add + 1 para contar ultimo comando que não é seguido por PIPE
}

void	apply_heredoc(t_cmd *cmd)
{
	int				heredoc_fd;
	t_file_heredoc	*current_file;

	current_file = cmd->heredocs->array[0];
	while (current_file)
	{
		heredoc_fd = open(current_file->file, O_RDONLY);
		if (heredoc_fd == -1)
		{
			perror("open heredoc");
			exit(EXIT_FAILURE);
		}
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
		current_file = current_file->next;
	}	
}
