/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:36:39 by gigardin          #+#    #+#             */
/*   Updated: 2024/08/16 20:48:58 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_heredoc(t_mini *temp_minishell)
{
	t_heredoc	*heredoc;
	
	heredoc = ft_calloc(sizeof(t_heredoc), 1);
	heredoc->size = count_cmd(temp_minishell->token);
	heredoc->array = ft_calloc(sizeof(t_file_heredoc *), heredoc->size);
	temp_minishell->heredocs = heredoc;
}

static void loop_exec_heredoc(int fd, int quotes, char *str_end)
{
	char *line;

	while(1)
	{
		line = readline("> ");
		if (!line)
		{
			//print error
			//ft_printf_fd(2, "%s %s %s (wanted `%s')\n, "Minishell:", "warning:", "here-document delimited by end-of-file". str_end)
			break ;
		}
		if (!ft_strcmp(line, str_end))
		{
			free(line);
			break ;
		}
		if (!quotes)
			line = expand_vars(line);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	write_file(char *file, int quotes, char *str_end)
{
	int	fd;
	//signal(SIGINT, copy_heredoc)
	
	//ft_rlstnew(str_end)
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);

	//função para fazer loop do heredoc (fd, quotes, str_end)
	close(fd);
	//ft_update_shell()->exit_status = 0; (refatorar função)
	clear_exit(ft_update_shell(), 1);
}

static int	execute_heredoc(char *str_end, unsigned int index, t_heredoc *heredoc, int is_first)
{
	char 		*file;
	pid_token	pid;
	int			exit_status;
	int			validate;
	validate = 0;

	file = get_file(is_first);
	add_file(&heredoc->array[index], new_file(file));

	pid = fork();
	if (pid == 0)
		write_file(file, check_quotes_in_token(str_end), remove_quotes(str_end));
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	
	//função para atualizar status de saída do shell
	if (exit_status == 130)
		return validate;
	else
		validate = 1;
	return (validate);
}

int	check_heredocs(t_mini *minishell)
{
	t_token	*temp_token;
	t_mini	*temp_minishell;
	int		validate;
	int		cmd_index; //para contabilizar todos cmds que tenho até chegar no hd
	
	validate = 0;
	cmd_index = 0;
	temp_minishell = minishell;
	temp_token = minishell->token;
	init_heredoc(temp_minishell);
	
	while(temp_token)
	{
		if (temp_token->type == PIPE)
			cmd_index++;
		else if (temp_token->type == HERE_DOC)
		{
			temp_minishell->heredocs->array[0] = new_file(temp_token->str);
			printf("%s", temp_minishell->heredocs->array[0]->file);
			if (!execute_heredoc(temp_token->next->str, cmd_index, minishell->heredocs, temp_token->prev = NULL))//função para executar o heredoc, chamar aqui e checando erro se não for o primeiro
			return (validate);
		}
		temp_token = temp_token->next;
		
	}

	return (validate);
}

