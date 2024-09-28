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
# include <string.h>
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
	int				type;
	char			*file;
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
	t_redir			*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_mini
{
	char		*input;
	char		**env_content;
	t_token		*token;
	t_cmd		*cmd;
	t_env		*env_exp;
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

t_mini			*ft_global_mini(t_mini *minishell);

/*adjust spaces*/
char			*adjust_spaces(char	*str);

/*alphabetical_sort*/
void			sort_env_list(t_env **env);
int				compare_keys(char *key1, char *key2);
void			insert_sorted(t_env **sorted, t_env *node);

/*built_ins*/
int				is_built_in(char *str);
void			execute_built_in(t_mini *minishell, t_cmd *cmd);

/*cd*/
int				execute_cd(t_mini *minishell);
int				execute_pwd(void);

/*echo*/
void			execute_echo(t_cmd *cmd);

/*env*/
void			execute_env(t_mini *minishell);

/* error functions*/
void			free_split(char **split);
void			free_cmds(t_cmd **cmd);
void			free_matrix(char **matrix);
void			error_function(char *str);

/*exit*/
void			execute_exit(t_mini *minishell);

/*export_utils*/
void			export_options(t_mini *minishell, t_cmd *cmd);
void			print_export(t_mini *minishell);
int				valid_var_name(char *str);

/*export*/
void			execute_export(t_mini *minishell, t_cmd *cmd);

/*expand_var_utils1*/
int				is_valid(char c, int position);
int				var_len(char *str);
char			*return_var(char *str, int add);
char			*return_key_content(t_mini *minishell, char *var_key);
int				add_variable_size(t_mini *minishell, char *token, int *i);

/*expand_var_utils2*/
int				calculate_size(t_mini *minishell, char *token);
void			append_to_result(char *result, char *str, int *j);
char			*get_env_value(t_env *env_list, const char *key);
int				expand_variable(t_mini *minishell, t_aux *aux);
int				is_variable_expandable(char *token, int pos, int quotes);

/*expand_var*/
char			*expand_token(t_mini *minishell, t_aux *aux, int quotes);
void			expand_all_tokens(t_mini *minishell);

/*free_functions*/
void			free_token(t_token **token);
void			free_cmds(t_cmd **cmd);
void			free_token_bc(t_token **token);
void			free_env(t_env **env);

/*free_heredocs*/
void			clean_heredoc_files(t_cmd *cmd);

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
void			process_multiple_cmds(t_mini minishell, int prev_fd);
void			handle_heredoc(t_token **token, unsigned int *count_cmd,
					t_cmd **cmd);
void			handle_redirection(t_token **token, t_cmd **cmd);
void			identify_type_cmd(t_token **token, t_cmd **cmd, char ***options,
					unsigned int *count_cmd);

/*make_token*/
t_token			*get_last_token(t_token *token);
void			make_tokens(t_token **token, char *split);
int				count_token_type(t_mini *minishell, int type_to_count);
int				has_token_type(t_mini minishell, int type_to_find);
int				find_etype(char *str);

/*make_env_list*/
void			list_env(t_env **env, char *split);
t_env			*get_last_env(t_env **token);

/*normalize*/
void			norme(t_mini *minishell, t_token *token);

/*make_env_list*/
void			make_env_list(t_mini *minishell);

/*process _cmds*/
void			process_multiple_cmds(t_mini minishell, int prev_fd);
/*process _cmds_utils*/
void			setup_file_descriptors(int input_fd, int out_fd);

/*unset*/
void			execute_unset(t_mini *minishell, t_cmd *cmd);
void			unset_env(t_env **env, char *key);

/*signal*/
void			setup_signals_heredoc(void);
void			copy_heredoc(int signal);
void			init_signals(void);
void			redonimation_readline(int signal);

/*heredoc_init*/
t_heredoc		*init_heredoc(t_mini *minishell);
int				execute_heredoc(const char *delimiter, unsigned int count_cmd,
					t_heredoc *heredocs, int is_first_cmd);
int				handle_fork(char *filename, const char *delimiter);
int				handle_filename(char *filename, t_heredoc *heredocs,
					unsigned int count_cmd);

/*heredoc_new_file*/
void			write_file(char *file, int quotes, const char *str_end,
					t_mini *minishell);
void			add_file(t_file_heredoc **array_file, t_file_heredoc *new_file);
t_file_heredoc	*get_last_file(t_file_heredoc *array_file);
char			*get_file(int is_first);
t_file_heredoc	*new_file(char *file);

/*heredoc_loop*/
void			process_line(char *line, int fd, int quotes, t_mini *minishell);
void			loop_exec_heredoc(int fd, int quotes, const char *str_end,
					t_mini *minishell);
int				print_error_heredoc(int i, const char *eof);

/*heredoc_utils*/
int				check_quotes_in_token(const char *str);
char			*remove_quotes(const char *str_end);
unsigned int	count_cmd(t_token *temp_token);
void			apply_heredoc(t_cmd *cmd);

/*execução redirect*/
void			apply_redirections(t_redir *redirs);
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

#endif
