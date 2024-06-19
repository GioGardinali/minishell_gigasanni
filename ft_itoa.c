/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:14:45 by asanni            #+#    #+#             */
/*   Updated: 2023/08/19 12:21:56 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	int	i;

	if (n < 0)
		i = 1;
	else
		i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*transf;
	int		size;

	size = ft_nlen(n);
	transf = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	transf = (char *)malloc(sizeof(char) * size + 1);
	if (!transf)
		return (NULL);
	transf[size] = '\0';
	if (n < 0)
	{
		n *= -1;
	}
	while (size--)
	{
		transf[size] = (n % 10) + 48;
		n = n / 10;
	}
	if (transf[0] == '0')
		transf[0] = '-';
	return (transf);
}
