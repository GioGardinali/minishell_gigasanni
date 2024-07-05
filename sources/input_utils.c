/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:11 by asanni            #+#    #+#             */
/*   Updated: 2024/07/05 18:52:50 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	remove_spaces(char	*str)
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
	*str_temp = '\0';
	return (str_temp);
}

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

// marcela's version
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

// marcela's version
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
	}
	return (validate);
}

//Renan's version
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
	}
	return (validate);
}

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
