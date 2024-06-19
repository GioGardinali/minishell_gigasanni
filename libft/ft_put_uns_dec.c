/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uns_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:55:39 by asanni            #+#    #+#             */
/*   Updated: 2023/10/31 20:19:34 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_uns_dec(unsigned int n)
{
	int	i;

	i = 0;
	if (n < 10)
	{
		i += ft_putchar_fd(n + 48, 1);
	}
	else
	{
		i += ft_put_uns_dec(n / 10);
		i += ft_put_uns_dec(n % 10);
	}
	return (i);
}
