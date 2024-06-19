/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:01:40 by asanni            #+#    #+#             */
/*   Updated: 2023/08/18 18:22:23 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*p_src;
	char	*p_dest;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	p_src = (char *)src;
	p_dest = (char *)dest;
	i = 0;
	while (i < n)
	{
		*(p_dest + i) = *(p_src + i);
		i++;
	}
	return (dest);
}
