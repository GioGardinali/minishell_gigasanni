/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:40:08 by asanni            #+#    #+#             */
/*   Updated: 2024/08/16 20:48:44 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**print_wrds(char **str, const char *s, int c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (s[len] != c && s[len])
		len++;
	str[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!str[i])
		return (NULL);
	ft_strlcpy(str[i], s, len + 1);
	i++;
	if (s[len] == c)
	{
		len++;
		str[i] = (char *)malloc(sizeof(char) * (ft_strlen(s + len) + 1));
		if (!str[i])
			return (NULL);
		ft_strlcpy(str[i], s + len, ft_strlen(s + len) + 1);
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split_two(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	print_wrds(split, s, c);
	return (split);
}
