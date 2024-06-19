/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:41:21 by asanni            #+#    #+#             */
/*   Updated: 2023/10/31 20:17:14 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_conversion(char *str, va_list(args), int i);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count_len;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	count_len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count_len += ft_find_conversion((char *)format, args, i);
		}
		else
			count_len += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(args);
	return (count_len);
}

static int	ft_find_conversion(char *str, va_list(args), int i)
{
	int	count;

	count = 0;
	if (str[i] == 'c')
		count += ft_putchar_fd(va_arg(args, int), 1);
	else if (str[i] == 's')
		count += ft_putstr_fd(va_arg(args, char *), 1);
	else if (str[i] == 'p')
		count += ft_put_pointer(va_arg(args, unsigned long int));
	else if (str[i] == 'd' || str[i] == 'i')
		count += ft_putnbr_fd(va_arg(args, int), 1);
	else if (str[i] == 'u')
		count += ft_put_uns_dec(va_arg(args, unsigned int));
	else if (str[i] == 'x')
		count += ft_puthex_lower(va_arg(args, unsigned int));
	else if (str[i] == 'X')
		count += ft_puthex_upper(va_arg(args, unsigned int));
	else if (str[i] == '%')
		count += ft_putchar_fd('%', 1);
	return (count);
}
