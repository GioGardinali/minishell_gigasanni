/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanni <asanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:52:55 by asanni            #+#    #+#             */
/*   Updated: 2024/06/23 19:12:23 by asanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void start_minishell(t_mini *minishell)
{
	char	**cmds;
	char	*path;
	pid_t	pid;

	minishell->input = readline("Minishelby> ");
	if (!minishell->input)
		minishell->input = ft_strdup("exit");
	if (ft_strcmp(minishell->input, ""))
		add_history(minishell->input);
	if (!ft_strcmp(minishell->input, "exit"))
	{
		//exit provisorio, teremos que fazer o nosso \o/
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (!pid)
	{
		cmds = ft_split(minishell->input, ' ');
		path = ft_strjoin(ft_strdup("/usr/bin/"), cmds[0]);
		execve(path, cmds, __environ);
		ft_putendl_fd("Execve falhou trouxa!", 2);
		free_split(cmds);
		free(path);
		exit(1);
	}
	free(minishell->input);
	waitpid(pid, NULL, 0);
}

int main (void)
{
	t_mini minishell;
	minishell = (t_mini){0};
	//minishell.env_args = getenv(__environ);
	while (1)
		start_minishell(&minishell);
	//free_envs(minishell.env_args);
	return (0);
}
