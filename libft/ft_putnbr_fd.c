/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:46:32 by asanni            #+#    #+#             */
/*   Updated: 2023/10/28 21:01:28 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (n == -2147483648)
// 		write(fd, "-2147483648", 11);
// 	else
// 	{
// 		if (n < 0)
// 		{
// 			ft_putchar_fd('-', fd);
// 			n *= -1;
// 		}
// 		if (n < 10)
// 		{
// 			ft_putchar_fd(n + 48, fd);
// 			return ;
// 		}
// 		else
// 			ft_putnbr_fd(n / 10, fd);
// 		ft_putnbr_fd(n % 10, fd);
// 	}
// }

/*versão printf*/
int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		i += write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			i += ft_putchar_fd('-', fd);
			n *= -1;
		}
		if (n < 10)
		{
			i += ft_putchar_fd(n + 48, fd);
		}
		else
		{
			i += ft_putnbr_fd(n / 10, fd);
			i += ft_putnbr_fd(n % 10, fd);
		}
	}
	return (i);
}
