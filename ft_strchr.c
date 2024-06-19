/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:23:35 by asanni            #+#    #+#             */
/*   Updated: 2023/12/11 20:03:58 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*versão gnl abaixo*/

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0' && (unsigned char)c != *s)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

/* funciona mas dá erro para reconhecer retangulo*/
// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s != '\0' && (unsigned char)c != *s)
// 	{
// 		if (*s == (unsigned char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	return (NULL);
// }
