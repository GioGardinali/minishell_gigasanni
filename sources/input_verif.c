/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:12:09 by asanni            #+#    #+#             */
/*   Updated: 2024/07/14 15:46:07 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_quotes(char	*str, int	*i)
{
	char	quote;

	if (str[(*i)] == 34 || str[(*i)] == 39)
	{
		quote = str[(*i)];
		while (str[(*i)] != quote)
			(*i)++;
	}
}

int	check_redirects(char *str)
{
	int	validate;
	int	i;

	validate = 0;
	i = 0;
	while (str[i] != '\0')
	{
		skip_quotes (str, &i);
		if (str[i] == '>' || str[i] == '<')
		{
			i++;
			if (str[i] != str[i + 1] && (str[i] == '>' || str[i] == '<'))
				return (-1);
			else
				i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '\0' || str[i] == '|'
				|| str[i] == '>' || str[i] == '<')
				validate = -1;
		}
		i++;
	}
	return (validate);
}

int	check_pipes(char *str)
{
	int	validate;
	int	i;

	validate = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '|')
		return (-1);
	while (str[i] != '\0')
	{
		skip_quotes (str, &i);
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '\0' || str[i] == '|')
				validate = -1;
		}
		i++;
	}
	return (validate);
}

int	check_quotes(char *str)
{
	char	quote;
	int		validate;
	int		i;

	validate = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote = str[i];
			i++;
			while (str[i] != quote && (str[i] != '\0'))
			{
				i++;
			}
			if (str[i] != quote)
			{
				validate = -1;
				break ;
			}
		}
		i++;
	}
	return (validate);
}

int	check_input(char *input)
{
	if (check_quotes(input))
		return (-1);
	if (check_redirects(input))
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		return (-1);
	}
	if (check_pipes(input))
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (-1);
	}
	return (0);
}

/*
Criar funções para verificar o input da readline
arruma-los e retorná-los certinho para passar
para a execve
*/

///colocar a validação do path nos redirects

// achar as aspas andar a string até achar uma igual a ela 
// dps
