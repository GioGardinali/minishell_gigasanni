/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_new_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:11:35 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/26 20:57:47 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file_heredoc	*new_file(char *file)
{
	t_file_heredoc	*n_file;

	n_file = ft_calloc(sizeof(t_file_heredoc), 1);
	if (!n_file)
		return (NULL);
	n_file->file = file;
	return (n_file);
}

char	*get_file(int is_first)
{
	char				*file_name;
	char				*tmp;
	static unsigned int	number;

	if (is_first)
		number = 0;
	tmp = ft_itoa(number);
	file_name = ft_strjoin(HERE_DOC_FILE, tmp);
	free(tmp);
	number++;
	return (file_name);
}

t_file_heredoc	*get_last_file(t_file_heredoc *array_file)
{
	while (array_file->next)
		array_file = array_file->next;
	return (array_file);
}

void	add_file(t_file_heredoc **array_file, t_file_heredoc *new_file)
{
	if (!new_file)
		return ;
	if (!*array_file)
		*array_file = new_file;
	else
		get_last_file(*array_file)->next = new_file;
}

void	write_file(char *file, int quotes, const char *str_end,
	t_mini *minishell)
{
	int	fd;

	signal(SIGINT, copy_heredoc);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	loop_exec_heredoc(fd, quotes, str_end, minishell);
	free((void *)str_end);
	close(fd);
}
