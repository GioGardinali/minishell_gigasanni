/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/11 20:20:23 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
esta função pega o input e faz todos os tratamentos que ele precisa
ela checa o prompt da readline
lida com os espaços da split
e cria os tokens com o resultado da split
tenho que arrumar a parte que lida com os cmds para passar para a execv
provavelmente melhor lidar com isso em outra função
*/

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

// void	skip_quotes2(char *input, int *i, char *temp, int *j)
// {
// 	char	quote;

// 	quote = input[*i];
// 	temp[(*j)] = input[(*i)];
// 	(*j)++;
// 	(*i)++;
// 	while (input[(*i)] != quote)
// 		temp[(*j)++] = input[(*i)++];
// 	temp[(*j)] = input[(*i)];
// 	(*j)++;
// }

// void	process_char(char *temp, int *j, int flg, int c)
// {
// 	if (c == ' ' || c == '\t')
// 		flg = 1;
// 	else if (!(c == ' ' || c == '\t'))
// 	{
// 		if (flg == 1)
// 		{
// 			temp[(*j)++] = ' ';
// 			flg = 0;
// 		}
// 		temp[(*j)] = c;
// 		(*j)++;
// 	}
// }

// void	remove_spaces(char *str, int i)
// {
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// }

// char	*adjust_spaces(char	*input)
// {
// 	char	*temp;
// 	int		flg;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	flg = 0;
// 	temp = malloc(sizeof(char) * ft_strlen(input) + 1);
// 	//remove_spaces(input, i);
// 	while (input[i])
// 	{
// 		if (input[i] == 34 || input[i] == 39)
// 		{
// 			if (flg)
// 				temp[j++] = ' ';
// 			skip_quotes2(input, &i, temp, &j);
// 			flg = 0;
// 		}
// 		else
// 			process_char(temp, &j, flg, input[i]);
// 		i++;
// 	}
// 	temp[j] = '\0';
// 	return (temp);
// }

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
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			quote = input[i];
			temp[j++] = input[i++];
			while (input[i] != quote)
			{
				temp[j++] = input[i++];
			}
			temp[j++] = input[i];
			temp[j] = -1;
			j++;
			i++;
		}
		else if (input[i] == ' ' || input[i] == '\t')
		{
			temp[j] = -1;
			j++;
		}
		else
			temp[j++] = input[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
// Tá imprimindo assim, falta tirar este lixo de memoria que está vindo junto
// ||
// |>>oi>>|
// |'ade    sanni'|
// |e|
// |'  gi    gardinali'|
// |!|
// |A|
// não precisa da adjust space
// transformar todos os espaços exceto as aspas em -1
// tratar o caso dos pipes e dos redirects grudados 
// tem que colocar um espçao antes de tokennizar ex: oi>>oi
