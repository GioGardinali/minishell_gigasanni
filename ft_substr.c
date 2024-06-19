/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:27:05 by asanni            #+#    #+#             */
/*   Updated: 2023/10/28 20:20:20 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	slen;

// 	slen = ft_strlen(s);
// 	if (start >= slen)
// 		return (ft_strdup(""));
// 	substr = NULL;
// 	if (len > (slen - start))
// 		len = slen - start;
// 	substr = (char *)malloc(sizeof(char) * len + 1);
// 	if (!s || !substr)
// 		return (NULL);
// 	if (substr)
// 		ft_strlcpy(substr, &s[start], len + 1);
// 	substr[len] = '\0';
// 	return (substr);
// }

/*gnl abaixo*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > (slen - start))
		len = slen - start;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!s || !substr)
		return (NULL);
	if (substr)
		ft_strlcpy(substr, &s[start], len + 1);
	substr[len] = '\0';
	return (substr);
}
