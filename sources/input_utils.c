/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/06 20:41:33 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*remove_spaces(char	*str)
// {
// 	int		i;
// 	char	*str_temp;

// 	i = 0;
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 	{
// 		if (!(str[i] == ' ' || str[i] == '\t'))
// 		{
// 			*str_temp = str[i];
// 			str_temp++;
// 		}
// 		i++;
// 	}
// 	*str_temp = '\0';
// 	return (str_temp);
// }

char	*normalize_input(t_mini *minishell)
{
	char	*input;
	char	**cmds;
	char	*cmd;
	int		i;

	input = minishell->input;
	check_input(input);
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

// char	*adjust_spaces(char	*str)
// {
// 	char	*temp;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	while (str[++i] != '\0')
// 	{
// 		if (str[i] == ' ')
// 			continue ;
// 		else
// 			j++;
// 	}
// 	temp = malloc(sizeof(char) * j + 1);
// 	i = -1;
// 	while (str)
// }

//usar a memmove ou a strlcpy

char	*adjust_spaces(char	*input)
{
	char	*temp;
	char	quote;
	int		flg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	flg = 0;
	temp = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (flg)
					temp[j++] = ' ';
			quote = input[i];
			temp[j] = input[i];
			i++;
			j++;
			while (input[i] != quote)
			{
				temp[j] = input[i];
				i++;
				j++;
			}
			temp[j] = input[i];
			i++;
			j++;
		}
		else
		{
			temp[j] = input[i];
			if (input[i] == ' ' || input[i] == '\t')
				flg = 1;
			else if (!(input[i] == ' ' || input[i] == '\t'))
			{
				if (flg)
					temp[j++] = ' ';
				flg = 0;
				temp[j] = input[i];
				j++;
			}
		}
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

// char	*adjust_spaces(char	*input)
// {
// 	char	*temp;
// 	int	i;

// 	i = 0;
// 	while (input[i] != '\0')
// 		ft_memmove(temp, input, ft_strlen(input));
// }

// char	*flag_str(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_isprint(str[i - 1]) && (str[i] == ' ' || str[i] == '\t'))
// 		{
// 			str[i] = '|';
// 		}
// 		i++;
// 	}
// }
