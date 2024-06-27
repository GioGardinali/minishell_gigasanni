/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:50:49 by asanni            #+#    #+#             */
/*   Updated: 2024/03/09 15:38:56 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h> // para adicionar no historico
# include <readline/readline.h> // para fazer tudo funfar
# include <sys/wait.h> // usar waitpid
# include "../libft/libft.h" /* mylibft */

//Structs
typedef struct s_env
{
	char			*env_key;
	char			**env_content;
	struct s_env	*next;
}t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

typedef struct s_mini
{
	char		*input;
	t_env		env;
	t_token		*comands;
}t_mini;

//Functions
char	*search_path(char **s, char *str);
char		*check_path(t_mini *minishell);

#endif
