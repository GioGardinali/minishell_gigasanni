/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenbetween.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:20:23 by asanni            #+#    #+#             */
/*   Updated: 2024/08/16 19:22:29 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_between(const char *s, char start, char end)
{
	size_t	len;

	len = 0;
	while (*s && *s != start)
		s++;
	if (!*s)
		return (0);
	s++;
	while (s[len] && s[len] != end)
		len++;
	return (len);
}
