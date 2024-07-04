/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:12:09 by asanni            #+#    #+#             */
/*   Updated: 2024/07/04 20:30:46 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char	*str)
{
	int	quote_nbr;
	int	validate;
	int	i;

	quote_nbr = 0;
	i = 0;
	validate = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			quote_nbr++;
		i++;
	}
	if (quote_nbr % 2 != 0)
		validate = -1;
	return (validate);
}

int	check_pipes(char	*str)
{
	int	validate;
	int	i;

	validate = 0;
	i = 0;
	while (str[i])
		i++;
	if (str[0] == 124 || str[i] == 124)
		validate = -1;
	return (validate);
}

int	check_redirect(char	*str)
{
	int		validate;

	if (check_input_and_trunc(str) == -1 || check_append(str) == -1)
		validate = -1;
	return (validate);
}

int	check_input_and_trunc(char	*str)
{
	char	*new_str;
	int		validate;
	int		i;

	validate = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{	
			while (str[++i] != '\0')
			{
				if (!ft_isprint(str[i]))
					validate = -1;
				i++;
			}
		}
		i++;
	}
	return (validate);
}

int	check_append(char	*str)
{
	char	*new_str;
	int		validate;
	int		i;
	int		j;

	validate = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{	
				while (str[++i] != '\0')
				{
					if (!ft_isprint(str[i]))
						validate = -1;
					i++;
				}
			}
		}
		i++;
	}
	return (validate);
}

//fazer o tratamento para o pipe e do NULL para o redirect > |

// int	check_input(char *input)
// {
// 	if (check_quotes(input))
// 		return (-1);
// 	if (check_redirect(input))
// 		return (-1);
// 	if (check_pipes(input))
// 		return (-1);
// 	return (0);
// }

/*
Criar funções para verificar o input da readline
arruma-los e retorná-los certinho para passar
para a execve
*/

///colocar a validação do path nos redirects
