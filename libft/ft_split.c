/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:19:39 by asanni            #+#    #+#             */
/*   Updated: 2023/08/19 14:21:59 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_part(const char *s, char c)
{
	size_t	i;
	size_t	part;

	i = 0;
	part = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			part++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (part);
}

static char	**print_wrds(char **str, const char *s, int c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (s[len] != c && s[len])
			len++;
		str[i] = (char *) malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		ft_strlcpy(str[i], s, len + 1);
		i++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	parts;

	if (!s)
		return (NULL);
	parts = count_part(s, c);
	split = (char **)malloc(sizeof (char *) * (parts + 1));
	if (!split)
		return (NULL);
	while (*s && *s == (unsigned char)c)
		s++;
	print_wrds(split, s, c);
	return (split);
}
