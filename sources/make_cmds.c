/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:39:02 by asanni            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/22 15:53:10 by gigardin         ###   ########.fr       */
=======
/*   Updated: 2024/09/21 13:34:06 by asanni           ###   ########.fr       */
>>>>>>> 1d2d5319e22e26fa33fe1d4a23d32cb4a5d5977c
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_redir(t_redir **redirs, int type, char *file);

void	handle_redirection(t_token **token, t_cmd **cmd)
{
	int	type;

	type = (*token)->type;
	*token = (*token)->next;
	if (*token != NULL)
		add_redir(&(*cmd)->redirs, type, (*token)->str);
	*token = (*token)->next;
}

void	handle_heredoc(t_token **token, unsigned int *count_cmd, t_cmd **cmd)
{
	if (!execute_heredoc((*token)->next->str, *count_cmd,
			(*cmd)->heredocs, (*token)->prev == NULL))
	{
		ft_putendl_fd("Heredoc error", 2);
		exit(EXIT_FAILURE);
	}
	*token = (*token)->next->next;
}

void	identify_type_cmd(t_token **token, t_cmd **cmd, char ***options,
	unsigned int *count_cmd)
{
	if (find_redir(*token) == 1)
		handle_redirection(token, cmd);
	else if ((*token)->type == HERE_DOC)
<<<<<<< HEAD
		handle_heredoc(token, count_cmd, cmd);
=======
	{
		printf("quantidade de comandos: %d\n", *count_cmd);
		*token = (*token)->next->next;
	}
>>>>>>> 1d2d5319e22e26fa33fe1d4a23d32cb4a5d5977c
	else
	{
		**options = ft_strdup((*token)->str);
		(*options)++;
		*token = (*token)->next;
	}
}

static char	**make_options(t_token **token, t_cmd **cmd,
	unsigned int *count_cmd)
{
	char	**options;
	char	**opt_bckp;
	int		len;

	len = 0;
	if (search_options(*token))
		return (NULL);
	len = return_len(*token);
	options = ft_calloc(sizeof(char *), (len + 1));
	opt_bckp = options;
	while (*token != NULL && (*token)->type != PIPE)
	{
		identify_type_cmd(token, cmd, &options, count_cmd);
	}
	return (opt_bckp);
}

void	add_redir(t_redir **redirs, int type, char *file)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->next = NULL;
	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	temp = *redirs;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}

void	make_one_cmd(t_cmd **cmd, t_token **token, t_mini *minishell,
	unsigned int *count_cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;
	char	**split;

	split = ft_split((*token)->str, ' ');
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (new_cmd == NULL)
		return ;
	new_cmd->str = ft_strdup(split [0]);
	new_cmd->heredocs = init_heredoc(minishell);
	new_cmd->options = make_options(token, &new_cmd, count_cmd);
	new_cmd->path = verify_path(minishell, new_cmd->str);
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = get_last_cmd(cmd);
	temp->next = new_cmd;
	new_cmd->prev = temp;
	free_matrix(split);
}

void	make_cmds(t_cmd **cmd, t_token **token, t_mini *minishell)
{
	unsigned int	count_cmd;

	count_cmd = 0;
	while (*token != NULL)
	{
		make_one_cmd(cmd, token, minishell, &count_cmd);
		if (*token != NULL && (*token)->type == PIPE)
		{
			*token = (*token)->next;
			count_cmd++;
		}
	}
}
