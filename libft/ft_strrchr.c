/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:24:43 by asanni            #+#    #+#             */
/*   Updated: 2023/08/18 18:25:35 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;

	len = ft_strlen(s);
	while (len && (char)c != *(s + len))
		len--;
	if ((char)c == *(s + len))
		return ((char *)(s + len));
	return (0);
}
