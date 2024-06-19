/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:01:27 by asanni            #+#    #+#             */
/*   Updated: 2023/08/18 18:22:04 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
	{
	unsigned char	*string;

	string = (unsigned char *)s;
	while (n--)
	{
		if (*string == (unsigned char) c)
			return (string);
		string++;
	}
	return (NULL);
}
