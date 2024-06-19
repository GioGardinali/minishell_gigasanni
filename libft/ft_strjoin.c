/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:07:43 by asanni            #+#    #+#             */
/*   Updated: 2023/10/28 20:23:05 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*newstr;
// 	int		i;
// 	int		j;

// 	newstr = NULL;
// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
// 	if (!newstr)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		newstr[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		newstr[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	newstr[i] = '\0';
// 	return (newstr);
// }

/*gnl abaixo*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index1;
	size_t	index2;
	char	*new_str;

	if (s1 == NULL)
		s1 = ft_strdup("");
	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	index1 = 0;
	while (s1[index1])
	{
		new_str[index1] = s1[index1];
		index1++;
	}
	index2 = 0;
	while (s2[index2])
	{
		new_str[index1 + index2] = s2[index2];
		index2++;
	}
	free((char *)s1);
	new_str[index1 + index2] = '\0';
	return (new_str);
}
