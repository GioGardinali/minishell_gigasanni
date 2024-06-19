/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:23:17 by asanni            #+#    #+#             */
/*   Updated: 2024/03/05 18:58:19 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *c)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (c[i])
	{
		if (ft_isdigit(c[i]) == 1)
			check = 1;
		else
			return (0);
		i++;
	}
	return (check);
}
