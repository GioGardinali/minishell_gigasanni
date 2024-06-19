/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:27:47 by asanni            #+#    #+#             */
/*   Updated: 2023/10/31 20:19:24 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_check_rest(int nbr);

int	ft_puthex_upper(unsigned int n)
{
	int		i;

	i = 0;
	if (n < 10)
	{
		i += ft_putchar_fd(n + 48, 1);
	}
	else if (n >= 10 && n < 16)
	{
		n = ft_check_rest(n);
		i += ft_putchar_fd(n, 1);
	}
	else
	{
		i += ft_puthex_upper(n / 16);
		i += ft_puthex_upper(n % 16);
	}
	return (i);
}

static char	ft_check_rest(int nbr)
{
	if (nbr % 16 == 10)
		return ('A');
	else if (nbr % 16 == 11)
		return ('B');
	else if (nbr % 16 == 12)
		return ('C');
	else if (nbr % 16 == 13)
		return ('D');
	else if (nbr % 16 == 14)
		return ('E');
	else if (nbr % 16 == 15)
		return ('F');
	return (0);
}
