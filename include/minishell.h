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
# include <stdbool.h>
# include <readline/history.h> // para adicionar no historico
# include <readline/readline.h> // para fazer tudo funfar
# include <sys/wait.h> // usar waitpid
# include "../libft/libft.h" /* mylibft */

//Structs

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*prev;
	struct s_env	*next;
}t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

typedef struct s_cmd
{
	char			*str;
	char			**options;
	char			*path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_mini
{
	char		*input;
	char		**env_content;
	t_token		*token;
	t_cmd		*cmd;
	t_env		*env_exp;

}t_mini;

typedef enum e_type
{
	VAR = 1,
	WORD,
	PIPE,
	INPUT,
	APPEND,
	TRUNC,
	HERE_DOC,
	QUOTES,
	DOC,
}	t_type;

//Functions
char	*check_path(t_mini *minishell);
char	**copy_env(t_mini *minishell);
char	*verify_path(t_mini *minishell, char *str);
int		check_input(char *input);
void	free_split(char **split);
void	free_cmds(t_cmd **cmd);
void	free_matrix(char **matrix);
void	error_function(char *str);
void	exit_function(void);
char	*adjust_spaces(char	*str);
void	skip_quotes(char	*str, int	*i);
void	make_tokens(t_token **token, char *split);
int		count_token_type(t_mini *minishell, int type_to_count);
int		has_token_type(t_mini minishell, int type_to_find);
t_token	*get_last_token(t_token **token);
t_cmd	*get_last_cmd(t_cmd **cmd);
int		find_etype(char *str);
int		build_pwd(void);
void	norme(t_mini *minishell, t_token *token);
void	make_cmds(t_cmd **cmd, t_token **token, t_mini *minishell);
int		find_redir(t_token *token);
int		search_options(t_token *token);
int		return_len(t_token *token);
void	free_token(t_token **token);
void	free_cmds(t_cmd **cmd);
void	free_token_bc(t_token **token);
void	process_two_cmds(t_mini minishell);
void	process_multiple_cmds(t_mini minishell, int prev_fd);
void	print_cmds(t_cmd *cmd); //apagar
void	print_options(char **options); //apagar
void	print_tokens(t_token *token); //apagar
void	print_matrix(char **matrix); // apagar
//void	process_multiple_cmds(t_mini minishell);
//void	prepare_split(char *str);
//void	skip_quotes2(char *input, int *i, char *temp, int *j);

#endif
