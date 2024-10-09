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
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# define HERE_DOC_FILE "/tmp/heredoc"

# define FAIL 1
# define SUCCESS 0

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

typedef struct s_ints
{
	int		double_q;
	int		single_q;
	int		i;
	int		j;
}t_ints;

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
	int			std_in;
	int			std_out;
	int			*pids;
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

//******************************Functions********************************//
/*adjust spaces*/
char			*adjust_spaces(char	*str);
void			handle_quotes(char **input, char **res_ptr, bool *in_quotes);

/*alphabetical_sort*/
void			sort_env_list(t_env **env);
int				compare_keys(char *key1, char *key2);
void			insert_sorted(t_env **sorted, t_env *node);

/*built_ins*/
int				is_built_in(char *str);
void			execute_built_in(t_mini *minishell, t_cmd *cmd);

/*cd*/
int				execute_cd(t_mini *minishell);

/*echo*/
int				execute_echo(t_cmd *cmd);

/*env*/
int				execute_env(t_mini *minishell);

/* error functions*/
void			free_split(char **split);
void			print_error(char *var, char *msg);
void			error_function(char *str);

/*exec_aux_cmds*/
void			execve_function(t_mini *minishell, char *path, char **options);
void			close_std_int_and_out(t_mini *minishell);

/*exec_redir*/
int				apply_redirection(int type, char *file);
int				apply_redirections(t_redir *redirs);

/*exit*/
int				kill_all(t_mini *minishell, int status);
int				exit_options(char **options);
int				execute_exit(t_mini *minishell, t_cmd *cmd);
int				update_exit_status(t_mini *minishell, int status);

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

/*export_utils*/
int				valid_var_name(char *str);
t_env			*duplicate_env(t_env *env_exp);
int				export_options(t_mini *minishell, t_cmd *cmd);
void			put_new_value(t_mini *minishell, char *var);

/*export*/
int				print_export(t_mini *minishell);
int				execute_export(t_mini *minishell, t_cmd *cmd);

/*free_functions*/
void			free_redirs(t_redir *redir);
void			free_token(t_token **token);
void			free_cmds(t_cmd **cmd);
void			free_matrix(char **matrix);
void			free_env(t_env **env);

/*free_functions2*/
void			clean_minishell(t_mini *minishell);
void			free_token_bc(t_token **token);
void			clean_exec_comand(t_mini *minishell);

/*free_heredocs*/
void			clean_heredoc_files(t_cmd *cmd);
void			clean_fork_heredoc(t_mini *minishell);

/*get_path*/
char			**copy_env(t_mini *minishell, char **env_list);
char			*verify_path(t_mini *minishell, char *str);
char			*search_path(char **s, char *str);
char			*remove_path(char *str);
char			*return_path(char *path_line, char *str);

/*handle_cmds_redirects*/
void			add_redir(t_redir **redirs, int type, char *file);
void			handle_redirection(t_token **token, t_cmd **cmd);
void			handle_heredoc(t_token **token, unsigned int *count_cmd,
					t_cmd **cmd);

/*heredoc_execution*/
void			process_line(char *line, int fd, int quotes, t_mini *minishell);
void			loop_exec_heredoc(int fd, int quotes, const char *str_end,
					t_mini *minishell);
void			print_error_heredoc(int i, const char *eof);
int				execute_heredoc(const char *delimiter, unsigned int count_cmd,
					t_heredoc *heredocs, t_token *token);

/*heredoc_init*/
t_mini			*ft_global_mini(t_mini *minishell);
t_heredoc		*init_heredoc(t_mini *minishell);
int				handle_fork(char *filename, const char *delimiter,
					t_heredoc *heredocs);
int				handle_filename(char *filename, t_heredoc *heredocs,
					unsigned int count_cmd);
void			quit_heredocs(t_heredoc *heredocs);

/*heredoc_new_file*/
void			write_file(char *file, int quotes, const char *str_end,
					t_mini *minishell);
void			add_file(t_file_heredoc **array_file, t_file_heredoc *new_file);
t_file_heredoc	*get_last_file(t_file_heredoc *array_file);
char			*get_file(int is_first);
t_file_heredoc	*new_file(char *file);

/*heredoc_utils*/
int				check_quotes_in_token(const char *str);
char			*remove_quotes(const char *str_end);
unsigned int	count_cmd(t_token *temp_token);
void			apply_heredoc(t_cmd *cmd);

/*input_verif*/
void			skip_quotes(char	*str, int	*i);
int				check_input(char *input);
int				check_redirects(char *str);
int				check_pipes(char *str);
int				check_quotes(char *str);

/*main*/
int				main(int argc, char **argv, char **env);

/*make_cmds_utils*/
int				find_redir(t_token *token);
int				return_len(t_token *token);
t_cmd			*get_last_cmd(t_cmd **cmd);
int				search_options(t_token *token);
void			last_cmd(t_cmd *temp, t_cmd **cmd, t_cmd *new_cmd);

/*make_cmd*/
void			make_cmds(t_cmd **cmd, t_token **token, t_mini *minishell);
void			identify_type_cmd(t_token **token, t_cmd **cmd, char ***options,
					unsigned int *count_cmd);

/*make_env_list*/
void			list_env(t_env **env, char *split);
t_env			*get_last_env(t_env **token);
void			make_env_list(t_mini *minishell);

/*make_token*/
t_token			*get_last_token(t_token *token);
void			make_tokens(t_token **token, char *split);
int				count_token_type(t_mini *minishell, int type_to_count);
int				has_token_type(t_mini minishell, int type_to_find);
int				find_etype(char *str);

/*normalize*/
int				norme(t_mini *minishell, t_token *token);

/*process _cmds*/
void			process_multiple_cmds(t_mini *minishell, int prev_fd);
pid_t			fork_and_execute(t_mini *minishell, int input_fd,
					int *out_fd, t_cmd *cmd);

/*process _cmds_utils*/
void			setup_file_descriptors(int input_fd, int out_fd);
void			close_fds(int *out_fd, int input_fd);
void			wait_and_update_exit_status(t_mini *minishell, int *pids);
int				is_first_and_builtin(t_mini *minishell);
int				return_pid(t_mini *minishell, t_cmd *cmd, int prev_fd,
					int fd[]);

/*process_cmds_utils1*/
void			fill_env_content(t_mini *minishell);

/*pwd*/
int				execute_pwd(void);

/*unset*/
int				execute_unset(t_mini *minishell, t_cmd *cmd);
void			unset_env(t_env **env, char *key);

/*signal*/
void			setup_signals_heredoc(void);
void			copy_heredoc(int signal);
void			init_signals(void);
void			redonimation_readline(int signal);
void			execution_signals(int pid);

/*verify_path*/
char			*verify_path(t_mini *minishell, char *str);

#endif
