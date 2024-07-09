/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/09 14:33:48 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*normalize_input(t_mini *minishell)
{
	char	*input;
	char	**cmds;
	char	*cmd;
	int		i;

	check_input(minishell->input);
	input = adjust_spaces(minishell->input);
	i = 0;
	while (cmds[i] != NULL)
	{
		cmd = ft_strjoin("/", cmds[i]);
		i++;
	}
	printf("%s", cmd);
	return (cmd);
}

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
int	
