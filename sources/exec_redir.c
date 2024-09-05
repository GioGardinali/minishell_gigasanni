/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigardin <gigardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:24 by gigardin          #+#    #+#             */
/*   Updated: 2024/09/05 19:39:25 by gigardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_cmd(t_cmd *cmd)
{
    int fd_in, fd_out, fd_append;

    if (cmd->input_file)
    {
        fd_in = open(cmd->input_file, O_RDONLY);
        if (fd_in < 0)
        {
            perror("open");
            return;
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }

    if (cmd->output_file)
    {
        fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0)
        {
            perror("open");
            return;
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }

    if (cmd->append_file)
    {
        fd_append = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_append < 0)
        {
            perror("open");
            return;
        }
        dup2(fd_append, STDOUT_FILENO);
        close(fd_append);
    }

    execve(cmd->path, cmd->options, environ);
    perror("execve");
}

void execute_cmds(t_cmd *cmd)
{
    pid_t pid;
    int status;

    while (cmd)
    {
        pid = fork();
        if (pid == 0)
        {
            execute_cmd(cmd);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
            return;
        }
        else
        {
            waitpid(pid, &status, 0);
        }
        cmd = cmd->next;
    }
}