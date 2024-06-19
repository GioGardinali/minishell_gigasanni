/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:00:53 by asanni            #+#    #+#             */
/*   Updated: 2023/12/12 19:43:17 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*print_line(char *str);
char	*save_rest(char *str);
char	*read_fd(int fd, char *rturn);

char	*get_next_line(int fd)
{
	static char	*save_read[1024];
	char		*aux;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	save_read[fd] = read_fd(fd, save_read[fd]);
	if (save_read[fd] == NULL)
		return (NULL);
	aux = print_line(save_read[fd]);
	save_read[fd] = save_rest(save_read[fd]);
	return (aux);
}

char	*print_line(char *str)
{
	char	*aux;
	char	*line;
	int		i;

	if (!str || str[0] == '\0')
		return (NULL);
	line = ft_strchr(str, '\n');
	if (line == NULL)
		return (ft_strdup(str));
	i = 0;
	while (str[i] != '\n')
		i++;
	aux = ft_substr(str, 0, i + 1);
	return (aux);
}

char	*save_rest(char *str)
{
	char	*save_res;
	int		size;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (i == 0 || str[i] == '\0' || str[i + 1] == '\0')
	{
		free (str);
		return (NULL);
	}
	size = ft_strlen(str);
	save_res = ft_substr(str, i + 1, (size - i));
	free(str);
	return (save_res);
}

char	*read_fd(int fd, char *rturn)
{
	ssize_t		size;
	char		*space;

	space = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!space)
		return (NULL);
	size = 1;
	while (!ft_strchr(rturn, '\n') && size > 0)
	{
		size = read(fd, space, BUFFER_SIZE);
		if (size < 0)
		{
			free(space);
			free(rturn);
			return (NULL);
		}
		space[size] = '\0';
		rturn = ft_strjoin(rturn, space);
	}
	free (space);
	return (rturn);
}
