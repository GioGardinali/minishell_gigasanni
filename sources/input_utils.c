/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/09 19:50:55 by gigardin         ###   ########.fr       */
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

void skip_quotes2(char *input, int *i, char *temp, int *j)
{
	char quote;

	quote = input[*i];
	temp[(*j)] = input[(*i)];
	(*j)++;
	(*i)++;
	while (input[(*i)] != quote)
		temp[(*j)++] = input[(*i)++];
	temp[(*j)] = input[(*i)];
	(*j)++;
}

void process_char(char *temp, int *j, int flg, int c) 
{
	if (c == ' ' || c == '\t')
		flg = 1;
	else if (!(c == ' ' || c == '\t'))
	{
		if (flg == 1)
		{
			temp[(*j)++] = ' ';
			flg = 0;
		}
		temp[(*j)] = c;
		(*j)++;
	}
}

void remove_spaces(char *str, int i)
{
	while(str[i] == ' ' || str[i] == '\t')
		i++;
}

char	*adjust_spaces(char	*input)
{
	char	*temp;
	int		flg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	flg = 0;
	temp = malloc(sizeof(char) * ft_strlen(input) + 1);
	remove_spaces(input, i);
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (flg)
				temp[j++] = ' ';
			skip_quotes2(input, &i, temp, &j);
			flg = 0;
		}
		else
			process_char(temp, &j, flg, input[i]);
		i++;
	}
	temp[j] = '\0';
	return (temp);
}


// char	*adjust_spaces(char	*input)
// {
// 	char	*temp;
// 	t_temp_input temp_value;
// 	int		flg;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	flg = 0;
// 	temp_value.str = malloc(sizeof(char) * ft_strlen(input) + 1);
// 	while (input[i] == ' ' || input[i] == '\t')
// 		i++;
// 	while (input[i])
// 	{
// 		if (input[i] == 34 || input[i] == 39)
// 		{
			
// 		}
// 		else
// 		{
// 			temp[j] = input[i];
// 			if (input[i] == ' ' || input[i] == '\t')
// 				flg = 1;
// 			else if (!(input[i] == ' ' || input[i] == '\t'))
// 			{
// 				if (flg)
// 					temp[j++] = ' ';
// 				flg = 0;
// 				temp[j] = input[i];
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	temp[j] = '\0';
// 	return (temp);
// }



// t_temp_input	*adjust_spaces_quotes(t_temp_input	*temp_value)
// {
// 	char			quote;
// 	int				flg;
// 	t_temp_input	value_temp;

// 	flg = 0;
// 	if (flg)
// 			temp[j++] = ' ';
// 	quote = input[i];
// 	temp[j] = input[i];
// 	i++;
// 	j++;
// 	while (input[i] != quote)
// 	{
// 		temp[j++] = input[i++];
// 	}
// 	temp[j] = input[i];
// 	i++;
// 	j++;
// 	value_temp.i = i;
// 	value_temp.j = j;
// 	value_temp.str = temp;
// 	value_temp.flg = flg;
// 	return (&value_temp);
// }



// char	*adjust_spaces(char	*input)
// {
// 	char	*temp;
// 	char	quote;
// 	int		flg;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	flg = 0;
// 	temp = malloc(sizeof(char) * ft_strlen(input) + 1);
// 	while (input[i] == ' ' || input[i] == '\t')
// 		i++;
// 	while (input[i])
// 	{
// 		if (input[i] == 34 || input[i] == 39)
// 		{
// 			if (flg)
// 					temp[j++] = ' ';
// 			quote = input[i];
// 			temp[j] = input[i];
// 			i++;
// 			j++;
// 			while (input[i] != quote)
// 			{
// 				temp[j++] = input[i++];
// 			}
// 			temp[j] = input[i];
// 			i++;
// 			j++;
// 		}
// 		else
// 		{
// 			temp[j] = input[i];
// 			if (input[i] == ' ' || input[i] == '\t')
// 				flg = 1;
// 			else if (!(input[i] == ' ' || input[i] == '\t'))
// 			{
// 				if (flg)
// 					temp[j++] = ' ';
// 				flg = 0;
// 				temp[j] = input[i];
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	temp[j] = '\0';
// 	return (temp);
// }