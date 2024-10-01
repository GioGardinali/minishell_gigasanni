/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:13:30 by asanni            #+#    #+#             */
/*   Updated: 2024/10/01 19:07:34 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes(char **input, char **res_ptr, bool *in_quotes)
{
	*in_quotes = !*in_quotes;
	*(*res_ptr)++ = *(*input)++;
}

static void	handle_space(char **input, char **res_ptr)
{
	*(*res_ptr)++ = -1;
	(*input)++;
}

static void	handle_special_chars(char **input, char **res_ptr)
{
	*(*res_ptr)++ = -1;
	*(*res_ptr)++ = *(*input)++;
	if ((**input == '<' && *(*input - 1) == '<')
		|| (**input == '>' && *(*input - 1) == '>'))
		*(*res_ptr)++ = *(*input)++;
	*(*res_ptr)++ = -1;
}

char	*adjust_spaces(char *input)
{
	size_t	length;
	char	*result;
	char	*res_ptr;
	bool	in_quotes;

	length = strlen(input);
	result = malloc(length * 4 + 1);
	res_ptr = result;
	in_quotes = false;
	while (*input == ' ')
		input++;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			handle_quotes(&input, &res_ptr, &in_quotes);
		else if (!in_quotes && *input == ' ')
			handle_space(&input, &res_ptr);
		else if (!in_quotes && (*input == '<'
				|| *input == '>' || *input == '|'))
			handle_special_chars(&input, &res_ptr);
		else
			*res_ptr++ = *input++;
	}
	*res_ptr = '\0';
	return (result);
}
