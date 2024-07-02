/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:12:09 by asanni            #+#    #+#             */
/*   Updated: 2024/07/02 20:31:41 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*normalize_input(t_mini *minishell)
{
	char	*input;
	char	**cmds;
	char	*cmd;
	int		i;

	input = minishell->input;
	cmds = ft_split(input, ' ');
	i = 0;
	while (cmds[i] != NULL)
	{
		cmd = ft_strjoin("/", cmds[i]);
		i++;
	}
	printf("%s", cmd);
	return (cmd);
}

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
	char	*new_str;
	int		validate;
	int		i;

	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{
				//remove_spaces(ft_strchr(str, ">>")); fazer uma strstr para este caso;
				printf(">>");
			}
			else
			{
				remove_spaces(ft_strchr(str, ">"));
			}
		}
		if (str[i] == '<')
			remove_spaces(ft_strchr(str, "<"));
		i++;
	}
}
//fazer o tratamento para o pipe e do NULL para o redirect; > |

char	remove_spaces(char *str)
{
	int		i;
	char	*str_temp;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
		{
			*str_temp = str[i];
			str_temp++;
		}
		i++;
	}
	return (str_temp);
}

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
