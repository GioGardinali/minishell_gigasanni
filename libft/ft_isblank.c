/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:15:29 by asanni            #+#    #+#             */
/*   Updated: 2024/08/25 17:30:04 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_blank(char *str)
{
	int	i;
	int	verif;

	i = 0;
	verif = 0;
	while (!(ft_isprint(str[i])) && str[i] != '\0')
	{
		if (str[i + 1] == '\0')
			verif = 1;
		i++;
	}
	return (verif);
}
