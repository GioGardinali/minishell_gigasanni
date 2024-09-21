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
# include <readline/readline.h> // para fazer tudo funcionar
# include <sys/wait.h> // usar waitpid
# include "../libft/libft.h" // libft
# include <signal.h> // fuction signal
# include <fcntl.h> // function open, close
# include <sys/stat.h> // criação de diretórios

# define HERE_DOC_FILE "/tmp/heredoc"

//Structs
typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*prev;
	struct s_env	*next;
}t_env;

typedef struct s_aux
{
	char	*result;
	char	*token;
	int		*i;
	int		*j;
}t_aux;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

typedef struct s_redir
{
	int				type; // Tipo de redirecionamento: REDIR_INPUT, REDIR_OUTPUT, REDIR_APPEND
	char			*file; // Nome do arquivo
	struct s_redir	*next;
}	t_redir;

typedef struct s_file_heredoc
{
	char					*file;
	struct s_file_heredoc	*next;

}	t_file_heredoc;

typedef struct s_heredoc
{
	t_file_heredoc		**array;
	int unsigned		size;

}	t_heredoc;

typedef struct s_cmd
{
	char			*str;
	char			**options;
	char			*path;
	t_heredoc		*heredocs;
	t_redir			*redirs; // List redirects
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_gc
{
	void				*content;
	struct s_gc			*next;
}						t_gc;

typedef struct s_mini
{
	char		*input;
	char		**env_content;
	t_token		*token;
	t_cmd		*cmd;
	t_env		*env_exp;
	t_gc		*gc;
	int			exit_status;
}	t_mini;

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
	EXPORT,
}	t_type;

typedef enum e_built
{
	ECHO = 1,
	CD,
	PWD,
	EXPT,
	UNST,
	ENV,
	EXIT,
}	t_built;

//Functions

/*adjust spaces*/
char			*adjust_spaces(char	*str);

/*alphabetical_sort*/
void			sort_env_list(t_env **env);

/*built_ins*/
int				is_built_in(char *str);
void			execute_built_in(t_mini *minishell, t_cmd *cmd);

/* error functions*/
void			free_split(char **split);
void			free_cmds(t_cmd **cmd);
void			free_matrix(char **matrix);
void			error_function(char *str);
void			exit_function(t_mini *minishell);

/*export_utils*/
void			export_options(t_mini *minishell, t_cmd *cmd);
void			print_export(t_mini *minishell);
int				valid_var_name(char *str);

/*export*/
void			execute_export(t_mini *minishell, t_cmd *cmd);

/*expand_var_utils*/
int				is_valid(char c, int position);
int				var_len(char *str);
char			*return_var(char *str, int add);
char			*return_key_content(t_mini *minishell, char *var_key);
int				add_variable_size(t_mini *minishell, char *token, int *i);

/*expand_var*/
char			*expand_token(t_mini *minishell, t_aux *aux);

/*free_functions*/
void			free_token(t_token **token);
void			free_cmds(t_cmd **cmd);
void			free_token_bc(t_token **token);
void			free_env(t_env **env);

/*get_path*/
char			**copy_env(t_mini *minishell);
char			*verify_path(t_mini *minishell, char *str);

/*input_verif*/
void			skip_quotes(char	*str, int	*i);
int				check_input(char *input);
char			*check_path(t_mini *minishell);

/*make_cmds_utils*/
int				find_redir(t_token *token);
int				return_len(t_token *token);
int				search_options(t_token *token);

/*make_cmd*/
void			make_cmds(t_cmd **cmd, t_token **token, t_mini *minishell);
t_cmd			*get_last_cmd(t_cmd **cmd);

/*make_token*/
t_token			*get_last_token(t_token **token);
void			make_tokens(t_token **token, char *split);
int				count_token_type(t_mini *minishell, int type_to_count);
int				has_token_type(t_mini minishell, int type_to_find);
int				find_etype(char *str);

/*make_env_list*/
void			list_env(t_env **env, char *split);
t_env			*get_last_env(t_env **token);

/*normalize*/
void			norme(t_mini *minishell, t_token *token);

/*process _cmds*/
void			process_multiple_cmds(t_mini minishell, int prev_fd);

/*unset*/
void			execute_unset(t_mini *minishell, t_cmd *cmd);

/*giovanna*/
int				check_quotes_in_token(char *str);
int unsigned	count_cmd(t_token *temp_token);
int				check_heredocs(t_mini *minishell);
t_file_heredoc	*new_file(char *file);
t_file_heredoc	*get_last_file(t_file_heredoc *array_file);
void			add_file(t_file_heredoc **array_file, t_file_heredoc *new_file);
char			*remove_quotes(char *str_token);
void			copy_heredoc(int signal);
void			free_here_docs(t_heredoc **heredoc);
void			ft_rlstnew(void *content);
char			*get_file(int is_first);
// t_mini			*ft_get_shell(void);
void			clear_exit(t_mini *minishell, int to_exit);
void			make_env_list(t_mini *minishell);
int				execute_heredoc(char *str_end, unsigned int index,
					t_heredoc *heredoc, int is_first);
void			loop_exec_heredoc(int fd, int quotes, char *str_end);
void			write_file(char *file, int quotes, char *str_end);
t_heredoc		*init_heredoc(t_mini *minishell);

/*execução redirect*/
void			apply_redirections(t_redir *redirs);
void			execute_cmd_redir(t_cmd *cmd, char **env_content);
void			execute_cmds_redir(t_cmd *cmd, char **env_content);

/*função perdida*/
int				build_pwd(void);

/*delete_later*/
void			print_env_list(t_env *env_list);
void			print_cmds(t_cmd *cmd); //apagar
void			print_options(char **options); //apagar
void			print_tokens(t_token *token); //apagar
void			print_matrix(char **matrix); // apagar
void			print_cmds_r(t_cmd *cmd); //apagar
//void	process_multiple_cmds(t_mini minishell);
//void	prepare_split(char *str);
//void	skip_quotes2(char *input, int *i, char *temp, int *j);
//int	execute_heredoc(char *str_end, unsigned int index,
//		t_heredoc *heredoc, int is_first);

#endif
