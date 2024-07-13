/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/13 18:02:49 by gigardin         ###   ########.fr       */
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
					temp[j++] = -1;
			quote = input[i];
			temp[j] = input[i];
			i++;
			j++;
			while (input[i] != quote)
			{
				temp[j++] = input[i++];
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
					temp[j++] = -1;
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

// void	remove_spaces(char *str, int i)
// {
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
	
// }

// char	*adjust_spaces(char	*input)
// {
// 	char	*temp;
// 	char	quote;
// 	int		i;
// 	int		j;
// 	t_token	token;

// 	i = 0;
// 	j = 0;
// 	token = (t_token){0};
// 	temp = malloc(sizeof(char) * ft_strlen(input) + 1);
// 	// ft_strtrim(input, " ");
// 	remove_spaces(input, i);
// 	while (input[i])
// 	{
// 		if (input[i] == 34 || input[i] == 39)
// 		{
// 			quote = input[i];
// 			temp[j] = input[i];
// 			i++;
// 			j++;
// 			while (input[i] != quote)
// 			{
// 				temp[j] = input[i];
// 				i++;
// 				j++;
// 			}
// 			temp[j] = input[i];
// 			j++;
// 			i++;
// 			temp[j++] = -1;
			
// 		}
// 		else if (input[i] == ' ' || input[i] == '\t')
// 			while (input[i] == ' ' || input[i] == '\t')
// 				i++;
// 		else if (!(input[i] == ' ' || input[i] == '\t'))
// 		{			
// 			while (input[i] != ' ' || input[i] != '\t')
// 			{
// 				temp[j] = input[i];
// 				j++;
// 				i++;
// 			}
// 			temp[j++] = -1;
// 		}
// 		i++;
// 	}
// 	temp[j] = '\0';
// 	return (temp);
// }


// void	search_quotes(char *input, int *i, char *temp, int *j)
// {
// 	if (input[i] == '>' && input[i++] == '>')
// 	{
// 	}
// }

// não precisa da adjust space
// transformar todos os espaços exceto as aspas em -1
// tratar o caso dos pipes e dos redirects grudados 
// tem que colocar um espçao antes de tokennizar ex: oi>>oi
