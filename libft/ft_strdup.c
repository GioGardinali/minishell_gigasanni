/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:09:54 by asanni            #+#    #+#             */
/*   Updated: 2023/10/28 20:18:11 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	char	*copy;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	copy = malloc (i + 1 * sizeof (char));
// 	if (!copy)
// 		return (NULL);
// 	if (*s == '\0')
// 	{
// 		copy[0] = '\0';
// 		return (copy);
// 	}
// 	i = 0;
// 	while (s[i])
// 	{
// 		copy[i] = s[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

/*gnl versão*/
char	*ft_strdup(const char *s)
{
	int		i;
	char	*copy;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	copy = malloc((i + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
