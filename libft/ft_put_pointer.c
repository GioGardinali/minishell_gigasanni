/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:55:46 by asanni            #+#    #+#             */
/*   Updated: 2023/10/31 20:19:45 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex_aux(unsigned long int n)
{
	int	i;

	i = 0;
	if (n > 15)
		i += ft_puthex_aux(n / 16);
	i += write(1, &HEX_LOW[n % 16], 1);
	return (i);
}

int	ft_put_pointer(unsigned long int p)
{
	int	count;

	count = 0;
	if (!p)
	{
		return (ft_putstr_fd("(nil)", 1));
	}
	count += ft_putstr_fd("0x", 1);
	count += ft_puthex_aux(p);
	return (count);
}
