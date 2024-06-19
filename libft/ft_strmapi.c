/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:57:45 by asanni            #+#    #+#             */
/*   Updated: 2023/08/18 18:25:07 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	int		len;

	if (!s)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	len = 0;
	if (!newstr)
		return (NULL);
	while (s[len] != '\0')
	{
		newstr[len] = f(len, s[len]);
		len++;
	}
	newstr[len] = '\0';
	return (newstr);
}
